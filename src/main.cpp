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
  auto db = std::make_unique<SQLite::Database>(
      db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  std::cout << "SQLite database file '" << db->getFilename().c_str()
            << "' opened successfully\n";

  auto in_queue = std::make_unique<ConcurrentQueue<int>>();
  auto out_queue = std::make_unique<ConcurrentQueue<int>>();
  auto worker = std::make_unique<Worker>(in_queue.get(), out_queue.get());
  auto db_writer = std::make_unique<DBWriter>(out_queue.get(), db.get());

  return App(std::move(worker), std::move(db_writer), std::move(in_queue),
             std::move(out_queue), std::move(db));
}

int main() {
  auto app = make_app(":memory:");
  app.run(500);
  app.stop();

  return 0;
}
