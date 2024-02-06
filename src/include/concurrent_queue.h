// concurrent-queue.h
#ifndef CONCURRENT_QUEUE_H_
#define CONCURRENT_QUEUE_H_

#include <condition_variable>
#include <expected>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

template <typename T> class ConcurrentQueue {
public:
  std::expected<T, std::string> pop() {
    std::unique_lock<std::mutex> mlock(mutex_);
    cond_.wait(mlock, [this] {
      return is_shutdown_ || (!queue_.empty() || is_done_);
    });

    if (!is_shutdown_ && !queue_.empty()) {
      auto val = queue_.front();
      queue_.pop();
      mlock.unlock();
      cond_.notify_one();
      return val;
    }

    if (queue_.empty() && is_done_) {
      return std::unexpected{"Queue is empty and marked as done."};
    }

    return std::unexpected{"Queue has shut down."};
  }

  void push(const T &item) {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }

  void shutdown() {
    is_shutdown_ = true;
    cond_.notify_one();
  }

  void close() {
    is_done_ = true;
    cond_.notify_one();
  }

  ConcurrentQueue() = default;
  ConcurrentQueue(const ConcurrentQueue &) = delete; // disable copying
  ConcurrentQueue &
  operator=(const ConcurrentQueue &) = delete; // disable assignment

private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
  bool is_shutdown_ = false;
  bool is_done_ = false;
};

#endif
