#include "include/db_writer.h"

void DBWriter::operator()() {
  std::cout << "db writer starting\n";
  while (true) {
    auto item = queue->pop();
    if (item) {
      std::cout << "DBWriter "
                << " popped " << item.value() << std::endl;
    } else {
      std::cout << "DBWriter got: " << item.error() << ". Quitting."
                << std::endl;
      ;
      break;
    }
  }
}
