#include "include/app.h"
#include "include/concurrent_queue.h"
#include "include/db_writer.h"
#include "include/worker.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

App make_app(std::string const &db_path) {
  auto db =
      SQLite::Database(db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  std::cout << "SQLite database file '" << db.getFilename().c_str()
            << "' opened successfully\n";

  return App(Worker(), DBWriter(db));
}

int main() {
  auto app = make_app(":memory:");
  app.run(500);
  app.stop();

  return 0;
}
