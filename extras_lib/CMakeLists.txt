set(LIB_SOURCES src/curses_util.cpp src/exception_util.cpp src/extra_util.cpp)

set(LIB_HEADERS inc/extras/curses_util.hpp inc/extras/exception_util.hpp inc/extras/extra_util.hpp)

add_library(extras_lib SHARED "${LIB_SOURCES}" "${LIB_HEADERS}")

target_include_directories(extras_lib PUBLIC inc)

target_compile_features(extras_lib PUBLIC cxx_std_17)
target_compile_features(extras_lib PUBLIC c_std_99)
