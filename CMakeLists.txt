cmake_minimum_required(VERSION 3.18)
project(sockpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -pthread)
# Build library sockpp
add_subdirectory(src)

add_executable(sockpp_main tests/main.cpp
        src/ClientSocket.cpp
        include/sockpp/ClientSocket.h)
target_include_directories(sockpp_main PRIVATE include)
target_link_libraries(sockpp_main sockpp)

