#include "include/app.h"

void App::run() {

  worker_thread = std::thread(*worker);
  db_writer_thread = std::thread(db_writer);
}

void App::stop() {

  in_queue.close();

  worker_thread.join();
  out_queue.close();
  db_writer_thread.join();
}
