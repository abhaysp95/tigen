set(LIB_SOURCES
	src/room.cpp
	src/sec_class.cpp
	src/instructor.cpp
	src/department.cpp
	src/class_time.cpp
	src/course.cpp
	src/data.cpp
	src/driver.cpp
	src/genetic_algo.cpp
	src/population.cpp
	src/schedule.cpp)

set(LIB_HEADERS
	inc/elib/class_time.hpp
	inc/elib/course.hpp
	inc/elib/department.hpp
	inc/elib/instructor.hpp
	inc/elib/room.hpp
	inc/elib/sec_class.hpp
	inc/glib/data.hpp
	inc/glib/driver.hpp
	inc/glib/genetic_algo.hpp
	inc/glib/population.hpp
	inc/glib/schedule.hpp)

add_library(tigen_lib SHARED "${LIB_SOURCES}" "${LIB_HEADERS}")
target_link_libraries(tigen_lib PRIVATE extras_library)
target_include_directories(tigen_lib PRIVATE ../tigen_lib/inc ../extras_lib/inc)
target_include_directories(tigen_lib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_features(tigen_lib PUBLIC cxx_std_17)
target_compile_features(tigen_lib PUBLIC c_std_99)
