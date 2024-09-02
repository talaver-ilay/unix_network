cmake_minimum_required(VERSION 3.5) # Проверка версии CMake.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(CMAKE_BUILD_TYPE Debug)

#------------------------LIB-----------------------------#
project(client_server)			# Название проекта

include_directories(/usr/lib/boost/boost)

file(GLOB 
            SERVER_SOURCE "server/src/*.cpp")
file(GLOB
            CLIENT_SOURCE "client/src/*.cpp")

add_executable(server ${SERVER_SOURCE})

add_executable(client ${CLIENT_SOURCE})