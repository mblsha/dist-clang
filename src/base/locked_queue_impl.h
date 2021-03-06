#pragma once

#include "base/locked_queue.h"

namespace dist_clang {
namespace base {

template <class T>
LockedQueue<T>::LockedQueue(size_t capacity)
  : capacity_(capacity) {
}

template <class T>
void LockedQueue<T>::Close() {
  std::unique_lock<std::mutex> lock(pop_mutex_);
  closed_ = true;
  pop_condition_.notify_all();
}

template <class T>
bool LockedQueue<T>::Push(T obj) {
  if (closed_) {
    return false;
  }

  {
    std::lock_guard<std::mutex> lock(pop_mutex_);
    if (queue_.size() >= capacity_ && capacity_ != UNLIMITED) {
      return false;
    }
    queue_.push(std::move(obj));
  }
  size_.fetch_add(1);
  pop_condition_.notify_one();

  return true;
}

template <class T>
typename LockedQueue<T>::Optional LockedQueue<T>::Pop() {
  std::unique_lock<std::mutex> lock(pop_mutex_);
  pop_condition_.wait(lock, [this]{ return closed_ || !queue_.empty(); });
  if (closed_ && queue_.empty()) {
    return Optional();
  }
  Optional&& obj = std::move(queue_.front());
  queue_.pop();
  size_.fetch_sub(1);
  return std::move(obj);
}

}  // namespace base
}  // namespace dist_clang
