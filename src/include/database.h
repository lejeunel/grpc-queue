#ifndef DATABASE_H_
#define DATABASE_H_
#include "models.h"
#include <iostream>
#include <memory>
#include <string>

enum class DBType { SQLite };

struct Config {
  std::string db_path;
};

class IDBSession {
public:
  virtual ~IDBSession() {}
  virtual void save_task(Task const &) = 0;
  virtual void init_tables() = 0;
  virtual int get_n_tasks() = 0;
};

class DBSessionCreator {
public:
  virtual std::unique_ptr<IDBSession> session_factory() = 0;
  std::unique_ptr<IDBSession> create() {
    auto s = this->session_factory();
    return s;
  }
};

#endif // DATABASE_H_
