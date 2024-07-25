cmake_minimum_required(VERSION 3.5) # Проверка версии CMake.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall")

set(CMAKE_BUILD_TYPE Debug) 

project(time_client)			# Название проекта

set(SOURCE_client_EXE client.cpp error.cpp)		# Установка переменной со списком исходников для исполняемого файла   

set(SOURCE_server_EXE server.cpp error.cpp)		# Установка переменной со списком исходников для исполняемого файла 

add_executable(client ${SOURCE_client_EXE})	# Создает исполняемый файл с именем main

add_executable(server ${SOURCE_server_EXE})	# Создает исполняемый файл с именем main
