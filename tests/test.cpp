#include "../src/include/app.h"
#include "../src/include/local_database.h"
#include <catch2/catch_test_macros.hpp>
#include <memory>

App make_test_app() {
  return App(std::make_unique<InMemoryDBCreator>(), std::make_unique<Worker>());
}

TEST_CASE("Should store tasks in DB", "[store]") {
  auto app = make_test_app();
  auto task = Task(0);
  app.push_task(task);
  app.run();
  app.stop();
  REQUIRE(app.get_db()->get_n_tasks() == 1);
}
