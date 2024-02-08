#ifndef DB_WRITER_H_
#define DB_WRITER_H_
#include "concurrent_queue.h"
#include "database.h"
#include "easylogging++.h"
#include "models.h"
#include <iostream>
#include <string>

class DBWriter {
public:
  void operator()();
  void set_in_queue(ConcurrentQueue<Task> &q) { queue = &q; }
  void set_db(IDBSession &a_db) { db = &a_db; }

private:
  ConcurrentQueue<Task> *queue;
  IDBSession *db;
};

#endif // DB_WRITER_H_
