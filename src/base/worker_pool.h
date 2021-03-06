#pragma once

#include "net/base/types.h"

#include <atomic>
#include <functional>
#include <thread>
#include <vector>

namespace dist_clang {
namespace base {

class WorkerPool {
  public:
    using NetWorker = std::function<void(const std::atomic<bool>&, net::fd_t)>;
    using SimpleWorker = std::function<void(const std::atomic<bool>&)>;

    WorkerPool();
    ~WorkerPool();

    void AddWorker(const NetWorker& worker, unsigned count = 1);
    void AddWorker(const SimpleWorker& worker, unsigned count = 1);

  private:
    std::vector<std::thread> workers_;
    std::atomic<bool> is_shutting_down_;
    net::fd_t self_pipe_[2];
};

}  // namespace base
}  // namespace dist_clang
