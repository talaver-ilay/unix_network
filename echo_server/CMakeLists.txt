cmake_minimum_required(VERSION 3.5) # Проверка версии CMake.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(CMAKE_BUILD_TYPE Debug)

project(echo_server)			# Название проекта

set(CLIENT_SOURCES
                    src/client.cpp
                    src/my_socket.cpp
                    src/error.cpp
)

set(SERVER_SOURCES
                    src/server.cpp
                    src/my_socket.cpp
                    src/error.cpp
)

include_directories("${PROJECT_SOURCE_DIR}/inc")

add_executable(client ${CLIENT_SOURCES})	# Создает исполняемый файл с именем main

add_executable(server ${SERVER_SOURCES})	# Создает исполняемый файл с именем main
