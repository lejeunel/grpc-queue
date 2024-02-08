#include "include/worker.h"

void Worker::operator()() {
  while (true) {
    auto item = in_queue->pop();
    if (item) {
      LOG(DEBUG) << "Worker processing task: " << item.value().id;
      out_queue->push(item.value());
    } else {
      LOG(DEBUG) << "Worker got: " << item.error() << ". Quitting.";
      ;
      break;
    }
  }
}
