#ifndef WORKER_H_
#define WORKER_H_

#include "concurrent_queue.h"
#include <iostream>
#include <string>

class Worker {
public:
  Worker(int const &id) : m_id(id){};
  Worker(ConcurrentQueue<int> *a_in_queue, ConcurrentQueue<int> *a_out_queue,
         int const &id)
      : in_queue(a_in_queue), out_queue(a_out_queue), m_id(id){};
  void operator()();

private:
  ConcurrentQueue<int> *in_queue;
  ConcurrentQueue<int> *out_queue;
  int m_id;
};

#endif // WORKER_H_
