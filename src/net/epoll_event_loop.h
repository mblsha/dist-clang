#pragma once

#include "base/attributes.h"
#include "net/base/types.h"
#include "net/event_loop.h"

#include <functional>
#include <mutex>
#include <unordered_set>

namespace dist_clang {
namespace net {

class EpollEventLoop: public EventLoop {
  public:
    typedef std::function<void(fd_t, ConnectionPtr)> ConnectionCallback;

    EpollEventLoop(ConnectionCallback callback);

    bool Handle(fd_t fd) THREAD_SAFE;

    virtual bool ReadyForRead(ConnectionPtr connection) THREAD_SAFE override;
    virtual bool ReadyForSend(ConnectionPtr connection) THREAD_SAFE override;

  private:
    virtual void DoListenWork(const volatile bool& is_shutting_down) override;
    virtual void DoIncomingWork(const volatile bool& is_shutting_down) override;
    virtual void DoOutgoingWork(const volatile bool& is_shutting_down) override;

    bool ReadyForListen(fd_t fd);
    ConnectionPtr AddConnection(fd_t fd);

    fd_t listen_fd_, incoming_fd_, outgoing_fd_;
    ConnectionCallback callback_;

    // We need to store listening fds - to be able to close them at shutdown.
    std::mutex listening_fds_mutex_;
    std::unordered_set<fd_t> listening_fds_;

    // We need to hold at least one pointer to each connection - to prevent
    // it's destruction.
    std::mutex connections_mutex_;
    std::unordered_set<ConnectionPtr> connections_;
};

}  // namespace net
}  // namespace dist_clang
