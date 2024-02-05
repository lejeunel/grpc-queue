#ifndef DB_WRITER_H_
#define DB_WRITER_H_
#include "concurrent_queue.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>

class DBWriter {
public:
  DBWriter(ConcurrentQueue<int> *a_queue, SQLite::Database *a_db)
      : queue(a_queue), db(a_db){};
  void operator()();

private:
  ConcurrentQueue<int> *queue;
  SQLite::Database *db;
};

#endif // DB_WRITER_H_
