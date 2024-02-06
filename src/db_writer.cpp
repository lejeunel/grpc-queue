#include "include/db_writer.h"

void DBWriter::operator()() {
  std::cout << "db writer starting\n";
  while (true) {
    auto task = queue->pop();
    if (task) {
      std::cout << "DBWriter: popped " << task.value().id << '\n';
      db->save_task(task);
    } else {
      std::cout << "DBWriter got: " << task.error() << '\n';
      ;
      break;
    }
  }
}
