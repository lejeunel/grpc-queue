#ifndef WORKER_H_
#define WORKER_H_

#include "concurrent_queue.h"
#include <iostream>
#include <string>

class Worker {
public:
  Worker(int const &id) : m_id(id){};
  Worker(ConcurrentQueue<int> *q, int const &id) : m_q(q), m_id(id){};
  void subscribe(ConcurrentQueue<int> *q);
  void operator()();

private:
  ConcurrentQueue<int> *m_q;
  int m_id;
};

#endif // WORKER_H_
