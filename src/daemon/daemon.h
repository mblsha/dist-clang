#pragma once

#include "base/attributes.h"
#include "base/queue_aggregator.h"
#include "daemon/configuration.h"
#include "daemon/file_cache.h"
#include "daemon/statistic.h"
#include "net/connection_forward.h"
#include "net/network_service.h"
#include "proto/remote.pb.h"

#include <unordered_map>

namespace dist_clang {

namespace base {
class Process;
}

namespace daemon {

class Daemon {
  public:
#if defined(PROFILER)
    Daemon();
#endif  // PROFILER
    ~Daemon();

    bool Initialize(const Configuration& configuration);

  private:
    using ScopedMessage = std::unique_ptr<proto::Universal>;
    using ScopedExecute = std::unique_ptr<proto::Execute>;
    using ScopedTask = std::pair<net::ConnectionPtr, ScopedExecute>;
    using Queue = base::LockedQueue<ScopedTask>;
    using QueueAggregator = base::QueueAggregator<ScopedTask>;
    using Optional = Queue::Optional;
    using CompilerMap =
        std::unordered_map<std::string /* version */, std::string /* path */>;
    using PluginNameMap =
        std::unordered_map<std::string /* name */, std::string /* path */>;
    using PluginMap =
        std::unordered_map<std::string /* version */, PluginNameMap>;

    bool SearchCache(const proto::Execute* message, FileCache::Entry* entry);
    void UpdateCache(const proto::Execute* message,
                     const proto::Status& status);
    bool FillFlags(proto::Flags* flags, proto::Status* status = nullptr);
    void HandleNewConnection(net::ConnectionPtr connection);
    bool HandleNewMessage(net::ConnectionPtr connection, ScopedMessage message,
                          const proto::Status& status);

    static std::unique_ptr<base::Process> CreateProcess(
        const proto::Flags& flags,
        const std::string& cwd_path = std::string());

    // Workers
    void DoCheckCache(const std::atomic<bool>& is_shutting_down);
    void DoRemoteExecution(const std::atomic<bool>& is_shutting_down,
                           net::EndPointPtr end_point);
    void DoLocalExecution(const std::atomic<bool>& is_shutting_down);

    CompilerMap compilers_;
    PluginMap plugins_;
    std::unique_ptr<FileCache> cache_;
    std::unique_ptr<net::NetworkService> network_service_;
    std::unique_ptr<daemon::Statistic> stat_service_;
    std::unique_ptr<Queue> local_tasks_;
    std::unique_ptr<Queue> failed_tasks_;
    std::unique_ptr<Queue> remote_tasks_;
    std::unique_ptr<Queue> cache_tasks_;
    std::unique_ptr<QueueAggregator> all_tasks_;
    std::unique_ptr<base::WorkerPool> workers_;
};

}  // namespace daemon
}  // namespace dist_clang
