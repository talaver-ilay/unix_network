cmake_minimum_required(VERSION 3.5) # Проверка версии CMake.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(CMAKE_BUILD_TYPE Debug)

#------------------------LIB-----------------------------#
project(client_server)			# Название проекта

include_directories(${PROJECT_SOURCE_DIR}/socket/inc)

file(GLOB 
            SOURCE_LIB "socket/src/*.cpp")
            
add_library(socket STATIC ${SOURCE_LIB})
#--------------------------------------------------------#

# link_directories(${CMAKE_SOURCE_DIR}/build)

# file(GLOB 
#             SERVER "${CMAKE_SOURCE_DIR}/server/*.cpp")

# add_executable(server ${SERVER})

# target_link_libraries(server libsocket.a)

# file(GLOB 
#             CLIENT "${CMAKE_SOURCE_DIR}/client/*.cpp")

# add_executable(client ${CLIENT})

# target_link_libraries(client libsocket.a)