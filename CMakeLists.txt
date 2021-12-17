cmake_minimum_required(VERSION 3.20)
project(abc5)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


add_executable(abc5 main.cpp Caller.cpp Caller.h)
target_link_libraries(abc5 PRIVATE Threads::Threads)
