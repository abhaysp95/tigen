// header file

#ifndef _GUARD_DATA_HPP_
#define _GUARD_DATA_HPP_

#include "../elib/department.hpp"
#include "../elib/course.hpp"
#include "../elib/instructor.hpp"
#include "../elib/room.hpp"
#include "../elib/class_time.hpp"

#include <vector>
#include <string>
#include <curses.h>
#include <menu.h>

extern const size_t DEMO_DEPTS_SIZE;
extern const size_t DEMO_COURSES_SIZE;
extern const size_t DEMO_INSTRUCTORS_SIZE;
extern const size_t DEMO_ROOMS_SIZE;
extern const size_t DEMO_CLASS_TIMES_SIZE;

typedef struct _show_item {
	char* selection;
	char** id;
	char** desc;
} SHOW_ITEM;

void print_in_middle( WINDOW* my_win, int starty, int startx, int width, std::string&& msg);
void print_footer( WINDOW* my_win, const char* msg = "Press 'q' to quit" );
void free_show_item( SHOW_ITEM* item_detail, int length );
void create_menu_win( MENU** my_menu, WINDOW** my_win, int max_item_size, const char* msg = "Select Item" );
void move_through_items( MENU* my_menu, WINDOW* my_win, SHOW_ITEM* item_detail );
void free_menu_and_items( MENU** my_menu, ITEM*** my_items, int count );
std::vector<std::string> get_selected_ids( char* selected_ids, const char* delim = " " );


namespace gen_algo {
	class data {   // <-- PARENT CLASS
		protected:
			std::vector<entities::department> _depts;
			std::vector<entities::course> _courses;
			std::vector<entities::instructor> _instructors;
			std::vector<entities::room> _rooms;
			std::vector<entities::class_time> _class_times;
			size_t _classes_count;
		public:
			data();
			data( long get_null );
			// accessors
			std::vector<entities::department> get_departments() const;
			std::vector<entities::course> get_courses() const;
			std::vector<entities::instructor> get_instructors() const;
			std::vector<entities::room> get_rooms() const;
			std::vector<entities::class_time> get_class_times() const;
			size_t get_classes_count() const;
	};

	class selection_data: public data {  // <-- CHILD1 CLASS
		private:
			void init_curses_selection( selection_data* obj );
		public:
			explicit selection_data( const data& data );

	};

	class demo_data: public data {  // <-- CHILD2 CLASS
		public:
			explicit demo_data( const data& data );
	};
};

#endif