#include "include/app.h"

void App::run(int const &n_items) {

  std::cout << "app pushing tasks in queue\n";
  for (int i = 0; i < n_items; ++i) {
    in_queue->push(i);
  }
}

void App::stop() {
  std::cout << "stopping app\n";

  in_queue->close();

  worker_thread.join();
  out_queue->close();
  db_writer_thread.join();
}
