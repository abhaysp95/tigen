if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	set(CURSES_NEED_NCURSES TRUE)
	find_package(Curses REQUIRED)

	find_library(CURSES_PANEL_LIBRARY NAMES panel DOC "The curses panel library")
	if (NOT CURSES_PANEL_LIBRARY)
		message(FATAL_ERROR "A required curses' panel library not found.")
	endif()

	find_library(CURSES_MENU_LIBRARY NAMES menu)
	if(NOT CURSES_MENU_LIBRARY)
		message(FATAL_ERROR "A required curses' menu library not found.")
	endif()

	set(CURSES_LIBRARIES "${CURSES_LIBRARIES}" "${CURSES_PANEL_LIBRARY}" "${CURSES_MENU_LIBRARY}")

	include_directories("${CURSES_INCLUDE_DIR}")

	#set(CURSES_CFLAGS "-lmenu")
endif()

add_executable(tigen main.cpp)
add_dependencies(tigen tigen_library)

target_include_directories(tigen PRIVATE "../extras_lib/inc" "../tigen_lib/inc")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	target_link_libraries(tigen PRIVATE "${CURSES_LIBRARIES}" extras_library tigen_library)
else()
	message(FATAL_ERROR "Can run only on Linux System for Now")
endif()
