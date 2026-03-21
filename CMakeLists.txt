cmake_minimum_required(VERSION 3.10)
project(TestMyTyping VERSION 1.0 LANGUAGES CXX)

set(CURSES_NEED_WIDE TRUE)

find_package(Curses REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE ${CURSES_LIBRARIES})
