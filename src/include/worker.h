#ifndef WORKER_H_
#define WORKER_H_

#include "concurrent_queue.h"
#include "easylogging++.h"
#include "models.h"
#include <iostream>
#include <string>

class Worker {
public:
  void operator()();
  void set_in_queue(ConcurrentQueue<Task> &q) { in_queue = &q; }
  void set_out_queue(ConcurrentQueue<Task> &q) { out_queue = &q; }

private:
  ConcurrentQueue<Task> *in_queue = nullptr;
  ConcurrentQueue<Task> *out_queue = nullptr;
};

#endif // WORKER_H_
