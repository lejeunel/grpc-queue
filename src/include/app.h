#ifndef APP_H_
#define APP_H_

#include "concurrent_queue.h"
#include "worker.h"

class App {
public:
  App(Worker *worker, ConcurrentQueue<int> *q) : m_worker(worker), m_q(q){};
  void run(int const &);

private:
  Worker *m_worker;
  ConcurrentQueue<int> *m_q;
};
#endif // APP_H_
