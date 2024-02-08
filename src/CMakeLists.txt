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

option(SOCI_CXX11 "" ON)
option(WITH_SQLITE3 "" ON)

set(SOCIDIR ${CMAKE_CURRENT_LIST_DIR}/thirdparty/soci)
add_subdirectory(${SOCIDIR})

# Needed so that SOCI can find the file soci/soci-config.h
target_include_directories(ccq
    PUBLIC
        ${SOCIDIR}/include)

target_link_libraries(ccq PUBLIC soci_core soci_sqlite3 grpc++)
target_link_libraries(main ccq)
