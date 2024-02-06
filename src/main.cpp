#include "include/app.h"
#include "include/concurrent_queue.h"
#include "include/database.h"
#include "include/db_writer.h"
#include "include/worker.h"
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

App make_test_app(Config const &cfg) {
  return App(std::make_unique<InMemoryDBCreator>());
}

int main() {
  auto app = make_test_app(Config{});
  app.run(500);

  app.stop();
  return 0;
}
