add_library(ccq
    worker.cpp
    db_writer.cpp
    app.cpp
    database.cpp
    logger.cpp
    easylogging++.cpp
)

add_executable(main
  main.cpp)


find_package(SQLite3 REQUIRED)
find_package(SOCI REQUIRED)

option(SOCI_CXX11 "" ON)
option(WITH_SQLITE3 "" ON)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/protos)

target_include_directories(ccq
    PUBLIC
        ${CMAKE_BINARY_DIR}/src/protos
      )


target_link_libraries(ccq PUBLIC SQLite::SQLite3 soci::soci rg_grpc_proto)
target_link_libraries(main ccq)
