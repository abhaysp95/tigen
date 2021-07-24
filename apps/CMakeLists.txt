add_executable(tigen main.cpp)
#add_dependencies(tigen extras_library)
add_dependencies(tigen tigen_library)

target_include_directories(tigen PUBLIC "../extras_lib/inc" "../tigen_lib/inc")

target_link_libraries(tigen PUBLIC extras_library tigen_library)
#target_link_libraries(tigen PUBLIC tigen_library)
