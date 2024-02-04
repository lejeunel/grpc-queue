#include "include/worker.h"

void Worker::operator()() {
  while (true) {
    auto item = in_queue->pop();
    if (item) {
      std::cout << "Worker " << m_id << " popped " << item.value()
                << " from in_queue\n";
      std::cout << "Worker " << m_id << " pushed " << item.value()
                << " to out_queue\n";
    } else {
      std::cout << "Worker " << m_id << " polled shut down queue. Quitting."
                << std::endl;
      ;
      break;
    }
  }
}
