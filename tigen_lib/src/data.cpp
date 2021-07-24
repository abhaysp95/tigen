// cpp file for "data.hpp"

//#include "../inc/data.hpp"
#include <glib/data.hpp>

//#include "../inc/extras/extra_util.hpp"
//#include "../inc/extras/curses_util.hpp"
#include <extras/extra_util.hpp>
#include <extras/curses_util.hpp>

#include <unordered_set>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <set>
#include <locale>

#include <iostream>  // it's temporary

template<typename t> struct TD;

const size_t DEMO_DEPTS_SIZE = 5;
const size_t DEMO_COURSES_SIZE = 14;
const size_t DEMO_INSTRUCTORS_SIZE = 15	;
const size_t DEMO_ROOMS_SIZE = 5;
const size_t DEMO_CLASS_TIMES_SIZE = 6;

void print_in_middle( WINDOW* my_win, int starty, int startx, int width, std::string&& msg ) {
	int length, x, y;
	float temp;

	if( NULL == my_win )
		my_win = stdscr;

	getyx( my_win, y, x );
	if( 0 != startx ) x = startx;
	if( 0 != starty ) y = starty;
	if( 0 == width ) width = 80;

	length = static_cast<int>( msg.size() );
	temp = ( width - length ) / 2.0;
	x = startx + ( int )temp;
	mvwprintw( my_win, y, x, "%s", msg.c_str() );
	wrefresh( my_win );
	//refresh();
}

void print_footer( WINDOW* my_win, const char* msg ) {
	move( LINES - 2, 4 );
	clrtoeol();
	mvwprintw( my_win, LINES - 2, 4, msg);
	wrefresh( my_win );
}

void free_show_item( SHOW_ITEM* item_detail, int length ) {
	if( NULL != item_detail->selection ) free( item_detail->selection );
	if( NULL != item_detail->id && NULL != item_detail->desc ) {
		for( int i = 0; i < length; i++ ) {
			if( NULL != item_detail->id[i] ) free( item_detail->id[i] );
			if( NULL != item_detail->desc[i] ) free( item_detail->desc[i] );
		}
	}
	if( NULL != item_detail->id ) free( item_detail->id );
	if( NULL != item_detail->desc ) free( item_detail->desc );
}

void create_menu_win( MENU** my_menu, WINDOW** my_win, int max_item_size, const char* msg) {
	int height = 0, width = 0;
	bool print_title{ true };
	if( 16 < LINES ) {
		int count_items = item_count( *my_menu );
		if( 24 < LINES ) {
			util::print_title_desc();
			if( LINES - 22 < count_items ) height = LINES - 18;
			else height = count_items + 4;
		}
		else {
			if( LINES - 14 < count_items ) height = LINES - 10;
			else height = count_items + 4;
		}
	}
	else height = LINES - 2;
	if( max_item_size + 7 < COLS ) {
		if( max_item_size + 10 < strlen( msg ) + 5 ) width = strlen( msg ) + 5;
		else width = max_item_size + 10;
	}
	else {
		if( max_item_size + 7 < strlen( msg ) + 5 ) print_title = false;
		width = max_item_size + 7;
	}

	if( 24 < LINES ) {
		*my_win = newwin( height, width, ( ( LINES - height ) / 2 ) + 4, ( COLS - width ) / 2 );
	}
	else *my_win = newwin( height, width, ( LINES - height ) / 2, ( COLS - width ) / 2 );
	keypad( *my_win, TRUE );

	set_menu_win( *my_menu, *my_win );
	set_menu_sub( *my_menu, derwin( *my_win, height - 4, width - 2, 3, 1 ) );
	set_menu_format( *my_menu, height - 4, 1 );

	set_menu_mark( *my_menu, " -> " );

	post_menu( *my_menu );
	wrefresh( *my_win );

	// make window better
	if( print_title ) print_in_middle( *my_win, 1, 1, width, msg );
	box( *my_win, 0, 0 );
	mvwaddch( *my_win, 2, 0, ACS_LTEE );
	mvwhline( *my_win, 2, 1, ACS_HLINE, width - 2 );
	mvwaddch( *my_win, 2, width - 1, ACS_RTEE );
	print_footer( stdscr, "<space> to select, arrow keys to move, <enter> to confirm selection, 'q' to move to next type['q' again to exit]" );
	refresh();
}

void move_through_items( MENU* my_menu, WINDOW* my_win, SHOW_ITEM* item_detail ) {
	int ch;

	while( ( ch = wgetch( my_win ) ) != 'q' ) {
		switch( ch ) {
			case KEY_DOWN:
				menu_driver( my_menu, REQ_DOWN_ITEM );
				break;
			case KEY_UP:
				menu_driver( my_menu, REQ_UP_ITEM );
				break;
			case ' ':
				menu_driver( my_menu, REQ_TOGGLE_ITEM );
				break;
			case 10:
				{
					ITEM** items;
					items = menu_items( my_menu );
					item_detail->selection[0] = '\0';
					for( int i = 0; i < item_count( my_menu ); i++ ) {
						if( TRUE == item_value( items[i] ) ) {
							strncat( item_detail->selection, item_name(items[i]), strlen( item_name( items[i] ) ) );
							strncat( item_detail->selection, " ", 1 );
						}
					}
					move( LINES - 4, 4 );
					clrtoeol();
					const char msg[20] = "You selected: ";
					mvprintw( LINES - 4, 4, msg );
					mvprintw( LINES - 4, strlen( msg ) + 5, item_detail->selection );
					refresh();
				}
				break;
			default:
				break;
		}
	}
}

// unpost menu and free items
void free_menu_and_items( MENU** my_menu, ITEM*** my_items, int count ) {
		if( NULL != *my_menu ) {
			unpost_menu( *my_menu );
			*my_menu = NULL;
		}
		for( int i = 0; i < count + 1; i++ ) {
			if( NULL != *( *my_items + i ) ) free_item( *( *my_items + i ) );  // or --> (*my_items)[i]
		}
		if( NULL != *my_items ) *my_items = NULL;
}

std::vector<std::string> get_selected_ids( char* selected_ids, const char* delim ) {
	std::vector<std::string> vec;
	char* token;
	token = strtok( selected_ids, delim );
	assert( NULL != token );
	while( NULL != token ) {
		vec.push_back( std::string{ token } );
		token = strtok( NULL, delim );
	}
	return vec;
}

template<typename T>
int create_id_desc( SHOW_ITEM* item_detail, const std::vector<T>& vec, int entity_size ) {

	int msg_size = -1e9;

	item_detail->selection = ( char* )calloc( ( entity_size * static_cast<int>( vec[0].get_id().size() ) ) + 100, sizeof( char ) ) ;

	item_detail->id = ( char** )calloc( entity_size, sizeof( char* ) );
	item_detail->desc = ( char** )calloc( entity_size, sizeof( char* ) );

	for( int i = 0; i < entity_size; i++ ) {
		int id_size = static_cast<int>( vec[i].get_id().size() );
		int name_size = static_cast<int>( vec[i].get_name().size() );
		item_detail->id[i] = ( char* )malloc( ( id_size + 1 ) * sizeof( char ) );
		item_detail->desc[i] = ( char* )malloc( ( name_size + 1 ) * sizeof( char ) );
		strncpy( item_detail->id[i], vec[i].get_id().c_str(), id_size + 1 );
		strncpy( item_detail->desc[i], vec[i].get_name().c_str(), name_size + 1 );
		if( ( id_size + name_size + 1 ) > msg_size ) msg_size = ( id_size + name_size + 1 );
	}
	return msg_size;
}

template<typename T>
std::vector<T> get_selected_entity( const std::vector<std::string>& selected_ids, const std::vector<T>& vec ) {
	std::vector<T> ret_vec;
	int pos{ 0 };
	for( int i = 0; i < static_cast<int>( vec.size() ); i++ ) {
		if( static_cast<int>( selected_ids.size() ) <= pos ) break;
		if( 0 == selected_ids.at( pos ).compare( vec.at(i).get_id() ) ) {
			ret_vec.push_back( vec[i] );
			pos++;
		}
	}
	return ret_vec;
}

template<typename T>
void get_selected_entity( const std::vector<std::string>& selected_ids, const std::vector<T>& vec, std::set<T>& tset ) {
	int pos{0};
	typename std::vector<T>::const_iterator citer = vec.cbegin();
	while( citer != vec.end() ) {
		if( static_cast<int>( selected_ids.size() ) <= pos ) break;
		if( 0 == selected_ids.at( pos ).compare( citer->get_id() ) ) {
			tset.insert( *citer );
			pos++;
		}
	}
}

template<typename T>
bool entity_comparator( const T& e1, const T& e2 ) {
	if( e1.get_id().empty() || e2.get_id().empty() ) return false;
	std::string e1_id{ e1.get_id() }, e2_id{ e2.get_id() };
	std::transform( begin( e1_id ), end( e1_id ), begin( e1_id ), []( unsigned char c ) {
			return std::tolower( c );
			} );
	std::transform( begin( e2_id ), end( e2_id ), begin( e2_id ), []( unsigned char c ) {
			return std::tolower( c );
			} );
	return e1_id < e2_id;
}

/** get the desired type set from the type of vector passed */
template<typename T>
std::set<T> get_entity_union( const std::vector<T>& for_type ) {
	return typename std::set<T>();
}

template<typename T>
void print_entity_names( const std::vector<T>& vec ) {
	for( const T& x: vec ) {
		std::cout << x.get_name() << '\n';
	}
}

namespace gen_algo {

	data::data(): _classes_count{ 0 } {  }

	/** data::data( NULL ) will create entities for data, but will not make any connection between entities( as for now ) */
	data::data( long get_null ): _classes_count{ 0 } {
		if( static_cast<long>( NULL ) != get_null ) {
			// write a logic here to terminate the program, until you haven't written a logic to use something instead of NULL
		}
		entities::room r1  ( "R1", "Room No. 1", 155 );
		entities::room r2  ( "R2", "Room No. 2", 170 );
		entities::room r3  ( "R3", "Room No. 3", 160 );
		entities::room r4  ( "R4", "Room No. 4", 180 );
		entities::room r5  ( "R5", "Room No. 5", 150 );
		entities::room r6  ( "R6", "Room No. 6", 130 );
		entities::room r7  ( "R7", "Room No. 7", 180 );
		entities::room r8  ( "R8", "Room No. 8", 164 );
		entities::room r9  ( "R9", "Room No. 9", 190 );
		entities::room r10 ( "R10", "Room No. 10", 140 );
		this->_rooms = std::vector<entities::room>{r1, r2, r3, r4, r5, r6, r7, r8, r9, r10};

		// classtimings
		entities::class_time ct1( "CT1", "MWF 09:00 - 11:00" );
		entities::class_time ct2( "CT2", "TTS 09:00 - 11:00" );
		entities::class_time ct3( "CT3", "MWF 12:00 - 14:00" );
		entities::class_time ct4( "CT4", "TTS 12:00 - 14:00" );
		entities::class_time ct5( "CT5", "MWF 15:00 - 17:00" );
		entities::class_time ct6( "CT6", "TTS 15:00 - 17:00" );
		entities::class_time ct7( "CT7", "MWF 18:00 - 20:00" );
		entities::class_time ct8( "CT8", "TTS 18:00 - 20:00" );
		this->_class_times = std::vector<entities::class_time>{ct1, ct2, ct3, ct4, ct5, ct6, ct7, ct8};

		// instructors for the batch
		entities::instructor i1 ( "I1", "Dr. Markandeya"   );
		entities::instructor i2 ( "I2", "Dr. Gautam"       );
		entities::instructor i3 ( "I3", "Dr. Bharadwaj"    );
		entities::instructor i4 ( "I4", "Dr. Shandilya"    );
		entities::instructor i5 ( "I5", "Dr. Angiras"      );
		entities::instructor i6 ( "I6", "Dr. Virajas"      );
		entities::instructor i7 ( "I7", "Dr. Kashyap"      );
		entities::instructor i8 ( "I8", "Dr. Satya"        );
		entities::instructor i9 ( "I9", "Dr. Kavya"        );
		entities::instructor i10( "I10", "Dr. Garg"        );
		entities::instructor i11( "I11", "Dr. Kapil"       );
		entities::instructor i12( "I12", "Dr. Kanad"       );
		entities::instructor i13( "I13", "Dr. Anusuya"     );
		entities::instructor i14( "I14", "Dr. Agastya"     );
		entities::instructor i15( "I15", "Dr. Vajashrava"  );
		entities::instructor i16( "I16", "Dr. Vachaspati"  );
		entities::instructor i17( "I17", "Dr. Kanada"      );
		entities::instructor i18( "I18", "Dr. Shushrut"    );
		entities::instructor i19( "I19", "Dr. Charak"      );
		entities::instructor i20( "I20", "Dr. VedVyasa"    );
		entities::instructor i21( "I21", "Dr. VarahMihira" );
		entities::instructor i22( "I22", "Dr. Sati"        );
		entities::instructor i23( "I23", "Dr. Janaki"      );
		entities::instructor i24( "I24", "Dr. Goswami"     );
		entities::instructor i25( "I25", "Dr. Parashar"    );
		entities::instructor i26( "I26", "Dr. Parashuram"  );
		entities::instructor i27( "I27", "Dr. Vaman"       );
		entities::instructor i28( "I28", "Dr. Yagyavalkya" );
		entities::instructor i29( "I29", "Dr. Nachiketa"   );
		entities::instructor i30( "I30", "Dr. Satyavan"    );
		this->_instructors = std::vector<entities::instructor>{ i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15,
				i16, i17, i18, i19, i20, i21, i22, i23, i24, i25, i26, i27, i28, i29, i30 };

		entities::course c1 ( "C1", "Automobile", 120            );
		entities::course c2 ( "C2", "Aeronautics", 150           );
		entities::course c3 ( "C3", "Metullurgy", 150            );
		entities::course c4 ( "C4", "Biological", 140            );
		entities::course c5 ( "C5", "Chemical", 150              );
		entities::course c6 ( "C6", "Embedded Programming", 120  );
		entities::course c7 ( "C7", "Web Development", 170       );
		entities::course c8 ( "C8", "Networking Security", 140   );
		entities::course c9 ( "C9", "Electronics", 130           );
		entities::course c10( "C10", "Robotics", 180             );
		entities::course c11( "C11", "GIS & Remote Sensing", 120 );
		entities::course c12( "C12", "Construction", 110         );
		entities::course c13( "C13", "Ceramic", 90               );
		entities::course c14( "C14", "UDCourse1", 130            );
		entities::course c15( "C15", "UDCourse2", 190            );
		entities::course c16( "C16", "UDCourse3", 129            );
		entities::course c17( "C17", "UDCourse4", 148            );
		entities::course c18( "C18", "UDCourse5", 160            );
		entities::course c19( "C19", "UDCourse6", 110            );
		entities::course c20( "C20", "UDCourse7", 110            );
		entities::course c21( "C21", "UDCourse8", 158            );
		this->_courses = std::vector<entities::course>{ c1, c2, c3, c4, c5, c6, c7,
			c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21 };

		entities::department d1( "D1", "Dept. of Mechanincal Engineering" );
		entities::department d2( "D2", "Dept. of NueroScience"            );
		entities::department d3( "D3", "Dept. of Information Technology"  );
		entities::department d4( "D4", "Dept. of Electrical Engineering"  );
		entities::department d5( "D5", "Dept. of Civil Engineering"       );
		entities::department d6( "D6", "Dept. of Undefined Name 1"        );
		entities::department d7( "D7", "Dept. of Undefined Name 2"        );
		this->_depts = std::vector<entities::department>{ d1, d2, d3, d4, d5, d6, d7 };
	}

	selection_data::selection_data( const data& data ) {

		ITEM** my_items = NULL;
		MENU* my_menu = NULL;
		//ITEM* cur_item = NULL;
		WINDOW* my_win = NULL;

		std::string win_message;

		SHOW_ITEM item_detail;
		item_detail.selection = NULL;
		item_detail.id = NULL;
		item_detail.desc = NULL;

		int max_item_size = 0, entity_size = 0;
		std::vector<std::string> selected_ids;

		initscr();
		cbreak();
		noecho();
		curs_set(0);  // change this to 0 later
		keypad( stdscr, TRUE );

		/*******************************
		********************************
		**  selection for department  **
		********************************
		*******************************/

		entity_size = static_cast<int>( data.get_departments().size() );

		/** fill up the items in C string to show as ITEM */
		max_item_size = create_id_desc( &item_detail, data.get_departments(), entity_size );

		my_items = ( ITEM** )calloc( entity_size + 1, sizeof( ITEM* ) );

		for( int i = 0; i < entity_size; i++ ) {
			my_items[i] = new_item( item_detail.id[i], item_detail.desc[i] );
		}
		my_items[entity_size] = new_item( ( char* )NULL, ( char* )NULL );

		// create menu
		my_menu = new_menu( ( ITEM** ) my_items );

		menu_opts_off( my_menu, O_ONEVALUE );  // select only one value( off )



		/************** this was just a test ************

		const char* temp = "temp";
		free( item_detail.id[0] );
		item_detail.id[0] = (char*)calloc(100, sizeof( char ));
		strncpy( item_detail.id[0], temp, strlen( temp ) + 1 );

		***********************************************/

		win_message = "Select Departments";
		create_menu_win( &my_menu, &my_win, max_item_size, win_message.c_str() );

		move_through_items( my_menu, my_win, &item_detail );

		free_menu_and_items( &my_menu, &my_items, entity_size );

		/** delemiting selection( item_detail.selection will be changed ) */
		selected_ids = get_selected_ids( item_detail.selection, " " );

		free_show_item(&item_detail, entity_size);

		// find the departments matching the id( copies entities from "data::<entity>" to "selection_data::<entity>" )
		this->_depts = get_selected_entity( selected_ids, data.get_departments() );


		/***************************
		****************************
		**  selection for course  **
		****************************
		***************************/

		entity_size = static_cast<int>( data.get_courses().size() );
		max_item_size = create_id_desc( &item_detail, data.get_courses(), entity_size );

		//this->_courses = std::vector<entities::course>( 10 );
		//size_t counter{ 0 };

		std::set<entities::course> crs_union;

		for( int i = 0; i < this->_depts.size(); i++ ) {
			if( NULL == my_items ) my_items = ( ITEM** )calloc( entity_size + 1, sizeof( ITEM* ) );

			for( int i = 0; i < entity_size; i++ ) {
				my_items[i] = new_item( item_detail.id[i], item_detail.desc[i] );
			}
			my_items[entity_size] = new_item( ( char* )NULL, ( char* )NULL );

			// create menu
			if( NULL == my_menu ) my_menu = new_menu( ( ITEM** ) my_items );

			menu_opts_off( my_menu, O_ONEVALUE );  // select only one value( off )

			win_message = "Select Course for Department[" + this->_depts[i].get_id() + "]";
			create_menu_win( &my_menu, &my_win, entity_size, win_message.c_str() );

			move_through_items( my_menu, my_win, &item_detail );

			//unpost_menu( my_menu );

			selected_ids = get_selected_ids( item_detail.selection, " " );
			std::vector<entities::course> current_courses = get_selected_entity( selected_ids, data.get_courses() );

			for( const entities::course& crs: current_courses ) {
				crs_union.insert( crs );
			}

			this->_depts[i].set_courses( current_courses );

			free_menu_and_items( &my_menu, &my_items, entity_size );
		}

		for( const entities::course& crs: crs_union ) this->_courses.push_back( crs );

		free_show_item( &item_detail, entity_size );

		/*******************************
		********************************
		**  selection for instructor  **
		********************************
		*******************************/

		entity_size = static_cast<int>( data.get_instructors().size() );
		max_item_size = create_id_desc( &item_detail, data.get_instructors(), entity_size );

		std::set<entities::instructor> inst_union;

		for( int i = 0; i < this->_courses.size(); i++ ) {
			if( NULL == my_items ) my_items = ( ITEM** )calloc( entity_size + 1, sizeof( ITEM* ) );

			for( int i = 0; i < entity_size; i++ ) {
				my_items[i] = new_item( item_detail.id[i], item_detail.desc[i] );
			}
			my_items[entity_size] = new_item( ( char* )NULL, ( char* )NULL );

			if( NULL == my_menu ) my_menu = new_menu( ( ITEM** ) my_items );

			menu_opts_off( my_menu, O_ONEVALUE );

			win_message = "Select Instructor for Course[" + this->_courses[i].get_id() + "]";
			create_menu_win( &my_menu, &my_win, entity_size, win_message.c_str() );

			move_through_items( my_menu, my_win, &item_detail );

			selected_ids = get_selected_ids( item_detail.selection, " " );
			std::vector<entities::instructor> current_instructors = get_selected_entity( selected_ids, data.get_instructors() );

			for( const entities::instructor& inst: current_instructors ) {
				inst_union.insert( inst );
			}

			this->_courses[i].set_instructors( current_instructors );

			for( size_t j = 0; j < this->_depts.size(); j++ ) {
				for( size_t k = 0; k < this->_depts[j].get_courses().size(); k++ ) {
					if( this->_depts[j].get_courses()[k] == this->_courses[i] ) {
						this->_depts[j].set_instructor_for_course( current_instructors, k );
						break;
					}
				}
			}

			free_menu_and_items( &my_menu, &my_items, entity_size );
		}

		for( const entities::instructor& inst: inst_union ) this->_instructors.push_back( inst );

		free_show_item( &item_detail, entity_size );

		/*******************************
		********************************
		**  selection for class_time  **
		********************************
		*******************************/

		entity_size = static_cast<int>( data.get_class_times().size() );
		max_item_size = create_id_desc( &item_detail, data.get_class_times(), entity_size );

		if( NULL == my_items ) my_items = ( ITEM** )calloc( entity_size + 1, sizeof( ITEM* ) );

		for( int i = 0; i < entity_size; i++ ) {
			my_items[i] = new_item( item_detail.id[i], item_detail.desc[i] );
		}
		my_items[entity_size] = new_item( ( char* )NULL, ( char* )NULL );

		if( NULL == my_menu ) my_menu = new_menu( ( ITEM** ) my_items );

		menu_opts_off( my_menu, O_ONEVALUE );

		win_message = "Select Class Times";
		create_menu_win( &my_menu, &my_win, max_item_size, win_message.c_str() );

		move_through_items( my_menu, my_win, &item_detail );

		free_menu_and_items( &my_menu, &my_items, entity_size );

		selected_ids = get_selected_ids( item_detail.selection, " " );

		this->_class_times = get_selected_entity( selected_ids, data.get_class_times() );

		free_show_item( &item_detail, entity_size );

		/**************************
		***************************
		**  selection for rooms  **
		***************************
		**************************/

		entity_size = static_cast<int>( data.get_rooms().size() );
		max_item_size = create_id_desc( &item_detail, data.get_rooms(), entity_size );

		if( NULL == my_items ) my_items = ( ITEM** )calloc( entity_size + 1, sizeof( ITEM* ) );

		for( int i = 0; i < entity_size; i++ ) {
			my_items[i] = new_item( item_detail.id[i], item_detail.desc[i] );
		}
		my_items[entity_size] = new_item( ( char* )NULL, ( char* )NULL );

		if( NULL == my_menu ) my_menu = new_menu( ( ITEM** ) my_items );

		menu_opts_off( my_menu, O_ONEVALUE );

		win_message = "Select Rooms";
		create_menu_win( &my_menu, &my_win, max_item_size, win_message.c_str() );

		move_through_items( my_menu, my_win, &item_detail );

		free_menu_and_items( &my_menu, &my_items, entity_size );

		selected_ids = get_selected_ids( item_detail.selection, " " );

		this->_rooms = get_selected_entity( selected_ids, data.get_rooms() );

		free_show_item( &item_detail, entity_size );


		endwin();

		/** for debugging purpose */
		/*std::cout << "Departments selected: \n";
		print_entity_names( this->_depts );

		std::cout << "Courses selected: \n";
		print_entity_names( this->_courses );

		std::cout << "Instructors selected: \n";
		print_entity_names( this->_instructors );

		std::cout << "Rooms selected: \n";
		print_entity_names( this->_rooms );

		std::cout << "Class time selected: \n";
		print_entity_names( this->_class_times );*/
	}



	/** this template is used to prepare data randomly for demo_data */
	template<typename push_from, typename push_to, typename t>
	void prepare_data(const push_from& obj1, push_to& obj2, const t count) {
		std::unordered_set<size_t> random_nums;
		while( random_nums.size() < count ) {
			random_nums.insert( util::rngi( obj1.size() ) );
		}
		std::for_each( begin( random_nums ), end( random_nums ), [ &obj1, &obj2 ]( const size_t x ) {
				obj2.push_back( std::move( obj1.at( x ) ) );
				} );
	}

	//void demo_data::make_connection( const data* data ) {
	demo_data::demo_data( const data& data ) {
		prepare_data( data.get_rooms(), this->_rooms, DEMO_ROOMS_SIZE );
		prepare_data( data.get_class_times(), this->_class_times, DEMO_CLASS_TIMES_SIZE );
		prepare_data( data.get_instructors(), this->_instructors, DEMO_INSTRUCTORS_SIZE );
		prepare_data( data.get_courses(), this->_courses, DEMO_COURSES_SIZE );
		prepare_data( data.get_departments(), this->_depts, DEMO_DEPTS_SIZE );

		// setup for course( is it possible to reduce this labour, check it again )
		this->_courses.at( 0 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[2], this->_instructors[4] });
		this->_courses.at( 1 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[4], this->_instructors[3] });
		this->_courses.at( 2 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[9] });
		this->_courses.at( 3 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[0], this->_instructors[6] });
		this->_courses.at( 4 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[3], this->_instructors[3] });
		this->_courses.at( 5 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[1] });
		this->_courses.at( 6 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[5], this->_instructors[9] });
		this->_courses.at( 7 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[1], this->_instructors[8] });
		this->_courses.at( 8 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[1], this->_instructors[11] });
		this->_courses.at( 9 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[10], this->_instructors[1], this->_instructors[13] });
		this->_courses.at( 10 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[10], this->_instructors[13] });
		this->_courses.at( 11 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[11], this->_instructors[14] });
		this->_courses.at( 12 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[12] });
		this->_courses.at( 13 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[1], this->_instructors[14] });

		// setup department
		this->_depts.at( 0 ).set_courses( std::vector<entities::course>{ this->_courses[0], this->_courses[1], this->_courses[2] } );
		this->_depts.at( 1 ).set_courses( std::vector<entities::course>{ this->_courses[3], this->_courses[4] } );
		this->_depts.at( 2 ).set_courses( std::vector<entities::course>{ this->_courses[5], this->_courses[6], this->_courses[7] } );
		this->_depts.at( 3 ).set_courses( std::vector<entities::course>{ this->_courses[8], this->_courses[9], this->_courses[10] } );
		this->_depts.at( 4 ).set_courses( std::vector<entities::course>{ this->_courses[11], this->_courses[12], this->_courses[13] } );

		// set the size of total course which are going to run
		for( const auto& dept: this->_depts ) this->_classes_count += dept.get_courses().size();
	}

	std::vector<entities::department> data::get_departments() const { return this->_depts; }

	std::vector<entities::course> data::get_courses() const { return this->_courses; }

	std::vector<entities::room> data::get_rooms() const { return this->_rooms; }

	std::vector<entities::instructor> data::get_instructors() const { return this->_instructors; }

	std::vector<entities::class_time> data::get_class_times() const { return this->_class_times; }

	size_t data::get_classes_count() const { return this->_classes_count; }
};












			/** test this logic with a demo */
			/*if( this->_courses.empty() ) this->_courses = current_courses;
			[>if( this->_courses.empty() ) {
				for( size_t i = 0; i < current_courses.size(); i++ ) {
					this->_courses[counter++] = current_courses[i];
				}
			}<]
			else {
				std::vector<entities::course>::const_iterator cciter{ current_courses.cbegin() };
				std::vector<entities::course>::const_iterator pos_iter;
				long idx{ 0 };
				while( cciter < current_courses.cend() ) {
					const std::vector<entities::course>::const_iterator start_find_pos{ this->_courses.cbegin() };
					pos_iter = find( start_find_pos + idx, this->_courses.cend(), *cciter );
					if( this->_courses.cend() == pos_iter ) {
						this->_courses.push_back( *cciter );
						//this->_courses[ counter++ ] = *cciter;
						//std::cout << "reached here\n";
					}
					else {
						idx = distance( start_find_pos, pos_iter );
					}
					cciter++;

				}
				sort( this->_courses.begin(), this->_courses.end(), entity_comparator<entities::course> );
			}*/