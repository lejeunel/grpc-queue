#ifndef APP_H_
#define APP_H_

#include "concurrent_queue.h"
#include "db_writer.h"
#include "worker.h"
#include <SQLiteCpp/SQLiteCpp.h>

class App {
public:
  App(Worker worker, DBWriter db_writer) {
    worker.set_in_queue(&in_queue);
    worker.set_out_queue(&out_queue);
    db_writer.set_in_queue(&out_queue);

    worker_thread = std::thread(worker);
    db_writer_thread = std::thread(db_writer);
  }
  void run(int const &);
  void stop();

private:
  std::thread worker_thread;
  std::thread db_writer_thread;
  ConcurrentQueue<int> in_queue;
  ConcurrentQueue<int> out_queue;
};

#endif // APP_H_
