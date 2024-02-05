#ifndef WORKER_H_
#define WORKER_H_

#include "concurrent_queue.h"
#include <iostream>
#include <string>

class Worker {
public:
  Worker(ConcurrentQueue<int> *a_in_queue, ConcurrentQueue<int> *a_out_queue)
      : in_queue(a_in_queue), out_queue(a_out_queue){};
  void operator()();

private:
  ConcurrentQueue<int> *in_queue;
  ConcurrentQueue<int> *out_queue;
};

#endif // WORKER_H_
