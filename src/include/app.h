#ifndef APP_H_
#define APP_H_

#include "concurrent_queue.h"
#include "db_writer.h"
#include "worker.h"
#include <SQLiteCpp/SQLiteCpp.h>

class App {
public:
  App(std::unique_ptr<Worker> a_worker, std::unique_ptr<DBWriter> a_db_writer,
      std::unique_ptr<ConcurrentQueue<int>> a_in_queue,
      std::unique_ptr<ConcurrentQueue<int>> a_out_queue,
      std::unique_ptr<SQLite::Database> a_db)
      : worker_thread(*std::move(a_worker)),
        db_writer_thread(*std::move(a_db_writer)),
        in_queue(std::move(a_in_queue)), out_queue(std::move(a_out_queue)),
        db(std::move(a_db)){};
  void run(int const &);
  void stop();

private:
  std::thread worker_thread;
  std::thread db_writer_thread;
  std::unique_ptr<ConcurrentQueue<int>> in_queue;
  std::unique_ptr<ConcurrentQueue<int>> out_queue;
  std::unique_ptr<SQLite::Database> db;
};

#endif // APP_H_
