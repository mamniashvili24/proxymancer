cmake_minimum_required(VERSION 3.28)
project(proxymancer)

set(CMAKE_CXX_STANDARD 20)
configure_file(src/config.txt ${CMAKE_CURRENT_BINARY_DIR}/config.txt COPYONLY)

add_executable(proxymancer src/main.cpp
        src/IOManager.cpp
        src/ServerConfig.cpp
        src/TcpSocketService.cpp
        src/IOManager.h
        src/ServerConfig.h
        src/TcpSocketService.h)
