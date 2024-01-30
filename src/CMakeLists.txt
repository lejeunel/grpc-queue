add_library(ccq
    concurrent_queue.cpp
    worker.cpp
    app.cpp
)

add_executable(main
  main.cpp)


target_link_libraries(main ccq)
