#ifndef LOCAL_DATABASE_H_
#define LOCAL_DATABASE_H_
#include "database.h"
#include "easylogging++.h"
#include "utils.h"
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

class LocalDBSession : public IDBSession {
public:
  LocalDBSession(std::string const &db_path) {
    session.open(soci::sqlite3, db_path);
  }
  void init_tables() {
    session << "CREATE TABLE IF NOT EXISTS tasks ( \
                    id UUID PRIMARY KEY, \
                    created_at VARCHAR(24), \
                    updated_at VARCHAR(24), \
                    deleted_at VARCHAR(24), \
                    field INT);";
  }
  void save_task(Task const &t) {
    session
        << "INSERT INTO tasks(id, field, created_at) values(:id, :field, :now)",
        soci::use(t.id), soci::use(t.field), Utils::datetime_now();
  }
  int get_n_tasks() {
    int count;
    session << "select count(*) from tasks", soci::into(count);
    return count;
  }

private:
  soci::session session;
};

class InMemoryDBCreator : public DBSessionCreator {

public:
  std::unique_ptr<IDBSession> session_factory() {
    return std::make_unique<LocalDBSession>(":memory:");
  };
};

#endif // LOCAL_DATABASE_H_
