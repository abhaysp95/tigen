cmake_minimum_required(VERSION 3.15)
project(tigen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER    "/usr/bin/clang")
set(CMAKE_C_FLAGS       "-Wall -std=c99")
set(CMAKE_C_FLAGS_DEBUG "-g")

set(CMAKE_CXX_COMPILER    /usr/bin/clang++)
set(CMAKE_CXX_FLAGS       "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
	src/extras/extra_util.cpp
	src/data.cpp
	src/room.cpp
	src/course.cpp
	src/schedule.cpp
	src/sec_class.cpp
	src/class_time.cpp
	src/department.cpp
	src/instructor.cpp
	src/population.cpp
	src/genetic_algo.cpp
	src/main.cpp
	)

add_executable(tigen "${SOURCES}")

include_directories(tigen inc src)
