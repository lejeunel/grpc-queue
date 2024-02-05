#ifndef WORKER_H_
#define WORKER_H_

#include "concurrent_queue.h"
#include <iostream>
#include <string>

class Worker {
public:
  void operator()();
  void set_in_queue(ConcurrentQueue<int> *q) { in_queue = q; }
  void set_out_queue(ConcurrentQueue<int> *q) { out_queue = q; }

private:
  ConcurrentQueue<int> *in_queue = nullptr;
  ConcurrentQueue<int> *out_queue = nullptr;
};

#endif // WORKER_H_
