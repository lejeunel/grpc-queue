#include "include/app.h"
#include "include/argparse.hpp"
#include "include/local_database.h"
#include "include/logger.h"
#include <memory>
INITIALIZE_EASYLOGGINGPP

App make_test_app() {
  return App(std::make_unique<InMemoryDBCreator>(), std::make_unique<Worker>());
}

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program("edksp", "0.1");

  program.add_argument("n").help("number of tasks").scan<'i', int>();

  int verbosity = 0;
  program.add_argument("-V")
      .action([&](const auto &) { ++verbosity; })
      .append()
      .default_value(false)
      .implicit_value(true)
      .help("verbosity level")
      .nargs(0);

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  configure_logger(el::Level::Error);
  if (verbosity == 1)
    configure_logger(el::Level::Debug);
  else if (verbosity > 1)
    configure_logger(el::Level::Trace);

  auto n = program.get<int>("n");
  LOG(DEBUG) << "n: " << n;

  auto app = make_test_app();
  for (int i = 0; i < n; ++i) {
    auto task = Task(i);
    app.push_task(task);
  }

  app.run();

  app.stop();
  return 0;
}
