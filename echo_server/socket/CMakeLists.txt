cmake_minimum_required(VERSION 3.5) # Проверка версии CMake.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(CMAKE_BUILD_TYPE Debug)

project(socket)			# Название проекта

include_directories(${PROJECT_SOURCE_DIR}/inc)

file(GLOB 
            SOURCE "src/*.cpp")
            
add_library(${PROJECT_NAME} STATIC ${SOURCE})