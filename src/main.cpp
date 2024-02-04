#include "include/app.h"
#include "include/concurrent_queue.h"
#include "include/worker.h"
#include <functional>
#include <iostream>
#include <thread>

int main() {
  ConcurrentQueue<int> in_queue;
  ConcurrentQueue<int> out_queue;

  using namespace std::placeholders;

  auto worker = Worker(&in_queue, &out_queue, 0);

  auto app = App(&worker, &in_queue);
  app.run(20);

  return 0;
}
