#ifndef DB_WRITER_H_
#define DB_WRITER_H_
#include "concurrent_queue.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>

class DBWriter {
public:
  DBWriter(SQLite::Database &a_db) : db(a_db){};
  void operator()();
  void set_in_queue(ConcurrentQueue<int> *q) { queue = q; }

private:
  ConcurrentQueue<int> *queue;
  SQLite::Database &db;
};

#endif // DB_WRITER_H_
