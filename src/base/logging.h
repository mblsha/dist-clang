#pragma once

#include <memory>
#include <set>
#include <sstream>

namespace dist_clang {
namespace base {

// Since the enum values are defined in the parent's scope - to be able to use
// something like this:
//
//     LOG(ERROR) << "Message";
//
// in any part of code, we need a separate namespace with an enum only, to
// include it with "using namespace NamedLevels;". See using_log.h file.

namespace named_levels {

// The |FATAL| is a special value: after LOG(FATAL) the program terminates with
// |exit(1)|.
enum {
  FATAL         =  0u,

  ERROR         = 10u,
  WARNING       = 20u,
  INFO          = 30u,
  VERBOSE       = 40u,

  CACHE_ERROR   = 41u,
  CACHE_WARNING = 42u,
  CACHE_INFO    = 43u,
  CACHE_VERBOSE = 44u,
};

}  // namespace NamedLevels

class Log {
  public:
    // First value is a right edge of interval, the second - a left edge.
    using RangeSet = std::set<std::pair<unsigned, unsigned>>;

    // Expects, that ranges are already filtered.
    static void Reset(unsigned error_mark, RangeSet&& ranges);

    Log(unsigned level);
    ~Log();

    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator= (const Log&) = delete;

    template <class T>
    Log& operator<< (const T& info);
    Log& operator<< (std::ostream& (*func)(std::ostream&));  // for |std::endl|

  private:
    static unsigned& error_mark();
    static std::shared_ptr<RangeSet>& ranges();

    unsigned level_;
    unsigned error_mark_;
    std::shared_ptr<RangeSet> ranges_;
    std::stringstream stream_;
};

// Use this class, if for some reason you can't include "using_log.h".
class DLog {
  public:
    DLog(unsigned level);

  private:
    std::unique_ptr<Log> log_;
};

template <class T>
Log& Log::operator<< (const T& info) {
  stream_ << info;
  return *this;
}

}  // namespace base
}  // namespace dist_clang
