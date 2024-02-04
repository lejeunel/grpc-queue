#ifndef DB_WRITER_H_
#define DB_WRITER_H_
#include "concurrent_queue.h"
#include <iostream>
#include <string>

class DBWriterWorker {
public:
  DBWriterWorker(int const &id) : m_id(id){};
  DBWriterWorker(ConcurrentQueue<int> *a_queue, int const &id)
      : queue(a_queue), m_id(id){};
  void operator()();

private:
  ConcurrentQueue<int> *queue;
  int m_id;
};

#endif // DB_WRITER_H_
