#ifndef DB_WRITER_H_
#define DB_WRITER_H_
#include "concurrent_queue.h"
#include "database.h"
#include "models.h"
#include <iostream>
#include <string>

class DBWriter {
public:
  DBWriter(IDBConn *a_db) : db(a_db){};
  void operator()();
  void set_in_queue(ConcurrentQueue<Task> *q) { queue = q; }

private:
  ConcurrentQueue<Task> *queue;
  IDBConn *db;
};

#endif // DB_WRITER_H_
