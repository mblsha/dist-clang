#pragma once

#include "base/thread_pool.h"

#include <string>

namespace dist_clang {
namespace daemon {

class FileCache {
  public:
    enum { UNLIMITED = 0 };
    using Entry = std::pair<std::string /* path */, std::string /* stderr */>;
    using Optional = base::ThreadPool::Optional;

    explicit FileCache(const std::string& path);
    FileCache(const std::string& path, uint64_t size_mb);

    bool Find(const std::string& code, const std::string& command_line,
              const std::string& version, Entry* entry) const;
    Optional Store(const std::string& code, const std::string& command_line,
                   const std::string& version, const Entry& entry);

  private:
    const std::string path_;
    base::ThreadPool pool_;
    uint64_t max_size_, cached_size_;

    void DoStore(const std::string& path, const std::string& code_hash,
                 const Entry& entry);
};

}  // namespace daemon
}  // namespace dist_clang
