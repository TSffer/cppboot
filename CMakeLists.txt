cmake_minimum_required(VERSION 3.12)
project(cppboot)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

include_directories(include)

add_library(cppboot
    src/core/application.cpp
    src/web/server.cpp
    src/web/controller.cpp
)

target_link_libraries(cppboot PRIVATE Boost::system Threads::Threads)

add_executable(hello_world examples/hello_world.cpp)
target_link_libraries(hello_world PRIVATE cppboot Boost::system Threads::Threads)