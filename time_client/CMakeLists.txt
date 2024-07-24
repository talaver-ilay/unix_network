cmake_minimum_required(VERSION 3.5) # Проверка версии CMake.
									# Если версия установленой программы
# 									# старее указаной, произайдёт аварийный выход.
set(CMAKE_CXX_STANDARD 23)

project(time_client)			# Название проекта

set(SOURCE_EXE client.cpp)		# Установка переменной со списком исходников для исполняемого файла                                 
set(CMAKE_BUILD_TYPE Debug)                    
add_executable(client ${SOURCE_EXE})	# Создает исполняемый файл с именем main
