#include "include/worker.h"

void Worker::operator()() {
  while (true) {
    auto item = in_queue->pop();
    if (item) {
      std::cout << "Worker popped " << item.value() << " from in_queue"
                << std::endl;
      out_queue->push(item.value());
      std::cout << "Worker pushed " << item.value() << " to out_queue"
                << std::endl;
    } else {
      std::cout << "Worker got: " << item.error() << ". Quitting." << std::endl;
      ;
      break;
    }
  }
}
