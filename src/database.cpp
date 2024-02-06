#include "include/database.h"

// std::unique_ptr<IDatabase> make_database(DBType const &type,
//                                          DBConfig const &cfg) {
//   if (type == DBType::SQLite) {
//     return std::make_unique<LocalDatabase>(
//         cfg.db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
//   }
// }
