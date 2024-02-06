#ifndef DATABASE_H_
#define DATABASE_H_
#include "models.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <memory>
#include <string>

enum class DBType { SQLite };

struct Config {
  std::string db_path;
};

class IDBConn {
public:
  virtual ~IDBConn() {}
  virtual void save_task(Task const &) = 0;
};

class LocalDatabase : public IDBConn {
public:
  LocalDatabase(std::string const &db_path, const int &flags)
      : db(db_path, flags) {}
  void save_task(Task const &t) { std::cout << "saving task " << t.id << '\n'; }

private:
  SQLite::Database db;
};

class DBCreator {
public:
  virtual std::unique_ptr<IDBConn> connection_factory_method() = 0;
  std::unique_ptr<IDBConn> create() {
    auto conn = this->connection_factory_method();
    return conn;
  }
};

class InMemoryDBCreator : public DBCreator {

public:
  std::unique_ptr<IDBConn> connection_factory_method() {
    auto flags = SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE;
    return std::make_unique<LocalDatabase>(":memory:", flags);
  };
};

#endif // DATABASE_H_
