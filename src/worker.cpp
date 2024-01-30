#include "include/worker.h"

void Worker::operator()() {
  while (true) {
    auto item = m_q->pop();
    std::cout << "Worker " << m_id << " popped " << item << "\n";
  }
}

void Worker::subscribe(ConcurrentQueue<int> *q) {
  std::cout << "Worker " << m_id << " subscribed to queue: " << q << std::endl;
  m_q = q;
}
