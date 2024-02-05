add_library(ccq
    worker.cpp
    db_writer.cpp
    app.cpp
)

add_executable(main
  main.cpp)

set(SQLITECPPDIR ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)
add_subdirectory(${SQLITECPPDIR})
target_link_libraries(ccq PUBLIC SQLiteCpp)

target_link_libraries(main ccq)
