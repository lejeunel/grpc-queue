#include "include/db_writer.h"

void DBWriterWorker::operator()() {
  while (true) {
    auto item = queue->pop();
    if (item) {
      std::cout << "DBWriter " << m_id << " popped " << item.value() << "\n";
    } else {
      std::cout << "DBWriter " << m_id << " polled shut down queue. Quitting."
                << std::endl;
      ;
      break;
    }
  }
}
