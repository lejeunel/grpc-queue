#include "include/db_writer.h"

void DBWriter::operator()() {
  while (true) {
    auto task = queue->pop();
    if (task) {
      LOG(DEBUG) << "DBWriter saving task: " << task.value().id;
      db->save_task(task.value());
    } else {
      LOG(DEBUG) << "DBWriter got: " << task.error();
      ;
      break;
    }
  }
}
