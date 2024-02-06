#ifndef APP_H_
#define APP_H_

#include "concurrent_queue.h"
#include "database.h"
#include "db_writer.h"
#include "models.h"
#include "worker.h"

class App {
public:
  App(std::unique_ptr<DBCreator> db_creator) {
    auto worker = Worker();
    db = db_creator->create();
    auto db_writer = DBWriter(db.get());
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
  ConcurrentQueue<Task> in_queue;
  ConcurrentQueue<Task> out_queue;
  std::unique_ptr<IDBConn> db;
};

#endif // APP_H_
