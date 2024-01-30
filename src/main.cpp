#include "include/app.h"
#include "include/concurrent_queue.h"
#include "include/worker.h"
#include <functional>
#include <iostream>
#include <thread>

int main() {
  ConcurrentQueue<int> q;

  using namespace std::placeholders;

  auto worker = Worker(0);
  worker.subscribe(&q);

  auto app = App(&worker, &q);
  app.run(20);

  // std::thread worker_thread(worker);
  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // worker_thread.join();
  return 0;
}
