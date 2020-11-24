cmake_minimum_required(VERSION 3.13)

project(saber VERSION 1.0 LANGUAGES CXX)

add_compile_options(
	-Werror
)

set(CMAKE_CXX_STANDARD 14)

include_directories(
	include
)

add_executable(saber
	src/main.cpp
	src/task_1.cpp
	src/task_2.cpp
	src/task_3.cpp
)
