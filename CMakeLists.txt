cmake_minimum_required(VERSION 3.10)

project(ccq CXX)

set(CMAKE_CXX_STANDARD 23)


find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)
