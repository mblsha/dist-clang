#pragma once

#include "base/hash.h"
#include "net/network_service.h"
#include "net/test_connection.h"

#include <unordered_map>

namespace std {

template <class T, class U>
struct hash<pair<T, U>> {
  public:
    size_t operator() (const pair<T, U>& value) const {
      size_t seed = 0;
      dist_clang::base::HashCombine(seed, value.first);
      dist_clang::base::HashCombine(seed, value.second);
      return seed;
    }
};

}  // namespace std

namespace dist_clang {
namespace net {

template <bool DoConnect = true>
class TestNetworkService: public NetworkService {
  public:
    using TestConnectionPtr = std::shared_ptr<TestConnection>;
    using This = TestNetworkService<DoConnect>;
    using OnConnectCallback = std::function<void(TestConnection*)>;
    using OnListenCallback =
        std::function<bool(const std::string&, unsigned short, std::string*)>;

    class Factory: public NetworkService::Factory {
      public:
        Factory() : on_create_([](This*) {}) {}

        virtual std::unique_ptr<NetworkService> Create() override {
          auto new_t = new This;
          on_create_(new_t);
          return std::unique_ptr<NetworkService>(new_t);
        }

        void CallOnCreate(std::function<void(This*)> callback) {
          on_create_ = callback;
        }

      private:
        std::function<void(This*)> on_create_;
    };

    TestNetworkService()
      : on_connect_([](TestConnection*) {}),
        on_listen_([](const std::string&, unsigned short, std::string*) {
          return false;
        }),
        connect_attempts_(nullptr), listen_attempts_(nullptr) {}

    virtual bool Run() override {
      return true;
    }

    virtual bool Listen(
        const std::string& path,
        ListenCallback callback,
        std::string* error) override {
      if (listen_attempts_) {
        (*listen_attempts_)++;
      }

      listen_callbacks_[std::make_pair(path, 0)] = callback;

      return on_listen_(path, 0, error);
    }

    virtual bool Listen(
        const std::string& host,
        unsigned short port,
        ListenCallback callback,
        std::string* error) override {
      if (listen_attempts_) {
        (*listen_attempts_)++;
      }

      listen_callbacks_[std::make_pair(host, port)] = callback;

      return on_listen_(host, port, error);
    }

    virtual ConnectionPtr Connect(
        EndPointPtr end_point,
        std::string* error) override {
      if (connect_attempts_) {
        (*connect_attempts_)++;
      }

      if (!DoConnect) {
        if (error) {
          error->assign("Test service rejects connection intentionally");
        }
        return ConnectionPtr();
      }
      else {
        auto new_connection = TestConnectionPtr(new TestConnection);
        on_connect_(new_connection.get());
        return new_connection;
      }
    }

    ConnectionPtr TriggerListen(const std::string& host, uint16_t port = 0,
                                bool on_connect = true) {
      auto it = listen_callbacks_.find(std::make_pair(host, port));
      if (it != listen_callbacks_.end()) {
        auto new_connection = TestConnectionPtr(new TestConnection);
        if (on_connect) {
          if (connect_attempts_) {
            (*connect_attempts_)++;
          }
          on_connect_(new_connection.get());
        }
        it->second(new_connection);
        return new_connection;
      }
      return ConnectionPtr();
    }

    void CallOnConnect(OnConnectCallback callback) {
      on_connect_ = callback;
    }

    void CallOnListen(OnListenCallback callback) {
      on_listen_ = callback;
    }

    void CountConnectAttempts(uint* counter) {
      connect_attempts_ = counter;
    }

    void CountListenAttempts(uint* counter) {
      listen_attempts_ = counter;
    }

  private:
    using HostPortPair = std::pair<std::string, unsigned short>;

    OnConnectCallback on_connect_;
    OnListenCallback on_listen_;
    uint* connect_attempts_;
    uint* listen_attempts_;
    std::unordered_map<HostPortPair, ListenCallback> listen_callbacks_;
};

}  // namespace net
}  // namespace dist_clang
