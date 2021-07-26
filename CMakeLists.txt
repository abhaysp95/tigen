cmake_minimum_required(VERSION 3.15...3.20)
project(tigen LANGUAGES CXX C VERSION 2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ====================================================
# Uncomment below lines if you are going to use clang
# (you can also modify these flags as per your need)
# ====================================================
if(NOT "${CMAKE_C_COMPILER}")
	set(CMAKE_C_COMPILER    "/usr/bin/clang")
	set(CMAKE_C_FLAGS       "-Wall -std=c99")
	set(CMAKE_C_FLAGS_DEBUG "-g")
endif()

if(NOT "${CMAKE_CXX_COMPILER}")
	set(CMAKE_CXX_COMPILER    "/usr/bin/clang++")
	set(CMAKE_CXX_FLAGS       "-Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(LIB_SOURCES
	extras_lib/src/curses_util.cpp
	extras_lib/src/exception_util.cpp
	extras_lib/src/extra_util.cpp)
set(LIB_HEADERS
	extras_lib/inc/extras/curses_util.hpp
	extras_lib/inc/extras/exception_util.hpp
	extras_lib/inc/extras/extra_util.hpp)

add_library(extras_library SHARED "${LIB_SOURCES}" "${LIB_HEADERS}")

target_include_directories(extras_library PRIVATE extras_lib/inc)

target_compile_features(extras_library PUBLIC cxx_std_17)
target_compile_features(extras_library PUBLIC c_std_99)

set(TIGEN_LIB_SOURCES
	tigen_lib/src/room.cpp
	tigen_lib/src/sec_class.cpp
	tigen_lib/src/instructor.cpp
	tigen_lib/src/department.cpp
	tigen_lib/src/class_time.cpp
	tigen_lib/src/course.cpp
	tigen_lib/src/data.cpp
	tigen_lib/src/driver.cpp
	tigen_lib/src/genetic_algo.cpp
	tigen_lib/src/population.cpp
	tigen_lib/src/schedule.cpp)
set(TIGEN_LIB_HEADERS
	tigen_lib/inc/elib/class_time.hpp
	tigen_lib/inc/elib/course.hpp
	tigen_lib/inc/elib/department.hpp
	tigen_lib/inc/elib/instructor.hpp
	tigen_lib/inc/elib/room.hpp
	tigen_lib/inc/elib/sec_class.hpp
	tigen_lib/inc/glib/data.hpp
	tigen_lib/inc/glib/driver.hpp
	tigen_lib/inc/glib/genetic_algo.hpp
	tigen_lib/inc/glib/population.hpp
	tigen_lib/inc/glib/schedule.hpp)

add_library(tigen_library SHARED "${TIGEN_LIB_SOURCES}" "${TIGEN_LIB_HEADERS}")
target_link_libraries(tigen_library PRIVATE extras_library)
target_include_directories(tigen_library PRIVATE tigen_lib/inc extras_lib/inc)

target_compile_features(tigen_library PUBLIC cxx_std_17)
target_compile_features(tigen_library PUBLIC c_std_99)

include_directories(tigen_lib/inc tigen_lib/src extras_lib/inc extras_lib/src)
add_subdirectory(apps)

if("${CMAKE_EXPORT_COMPILE_COMMANDS}")
	if(EXISTS "${CMAKE_BINARY_DIR/compile_commands.json}" AND NOT IS_DIRECTORY "${CMAKE_BINARY_DIR}/compile_commands.json")
		execute_process(COMMAND ln -f -s "${CMAKE_BINARY_DIR}/compile_commands.json" "${CMAKE_SOURCE_DIR}/compile_commands.json"
			RESULT_VARIABLE LN_RESULT)
		if(NOT LN_RESULT EQUAL "0")
			message(STATUS "Can't create symlink for compile_commands.json")
		endif()
	endif()
else()
	message(STATUS "CMAKE_EXPORT_COMPILE_COMMANDS is OFF")
endif()

