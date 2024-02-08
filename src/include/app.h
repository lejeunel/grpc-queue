#ifndef APP_H_
#define APP_H_

#include "concurrent_queue.h"
#include "database.h"
#include "db_writer.h"
#include "easylogging++.h"
#include "models.h"
#include "worker.h"

class App {
public:
  App(std::unique_ptr<DBSessionCreator> db_creator,
      std::unique_ptr<Worker> a_worker) {
    worker = std::move(a_worker);
    db = db_creator->create();
    db->init_tables();
    db_writer = DBWriter();
    db_writer.set_db(*db);
    worker->set_in_queue(in_queue);
    worker->set_out_queue(out_queue);
    db_writer.set_in_queue(out_queue);
  }
  void run();
  void stop();
  void push_task(Task &t) { in_queue.push(t); }
  IDBSession *get_db() { return db.get(); };

private:
  std::thread worker_thread;
  std::thread db_writer_thread;
  ConcurrentQueue<Task> in_queue;
  ConcurrentQueue<Task> out_queue;
  std::unique_ptr<IDBSession> db;
  std::unique_ptr<Worker> worker;
  DBWriter db_writer;
};

#endif // APP_H_
