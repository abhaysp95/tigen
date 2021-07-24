// main file

#include <glib/driver.hpp>
#include <extras/curses_util.hpp>

#include <iostream>
#include <ios>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include <cstdlib>
#include <cxxabi.h>
#include <random>
#include <chrono>
#include <stdexcept>
#include <cstring>

#include <ncurses.h>
#include <panel.h>

#define VERSION 1.3
#define DSIZE 3

// use this when you want info for ncurses printing
//#define DEBUG_CURSES

std::vector<std::string> tab_names = {
	"[Data]",
	"[Generations]",
	"[Result]"
};

std::vector<std::string> new_lines;

bool check_screen_dimensions();
void run_driver( std::string&& type="demo" );
void print_help();
int print_with_ncurses();
void init_pads(std::vector<util::WIN>& wins, const std::vector<std::vector<std::string>::size_type>& pheights,
		const std::vector<std::vector<std::string>::size_type>& pwidths);
void init_win(util::WIN& win, const int pheight, const int pwidth);
void print_tab_names(std::vector<util::WIN>& wins, int cur_tab_num);
void write_data_to_pads(std::vector<util::WIN>& wins, const std::vector<std::vector<std::string>>& result_data);
void write_to_pad(WINDOW* win, const std::vector<std::string>& vec_str);

template <typename T>
void print_vec(const std::vector<T>& vec) {
	for (const T& x: vec)
		std::cout << x << '\n';
}

int main(int argc, char** argv) {
	if (argc >= 2) {
		if (strncmp(*(argv + 1), "--help", 6) == 0) {
			print_help();
		}
		else if (strncmp(*(argv + 1), "--version", 9) == 0) {
			std::cout << "tigen-" << VERSION << '\n';
		}
		else if (strncmp(*(argv + 1), "--tui", 5) == 0) {
			/***********************************************************
			* Update this part for ncurses selection and printing both *
			************************************************************/
			bool is_valid = check_screen_dimensions();
			if( is_valid ) {
				run_driver( "select" );
				int status = print_with_ncurses();
				if (status == -1) {
					print_vec(data_avail_to_print);
					print_vec(gen_data_to_print);
					print_vec(fittest_schedule_to_print);
				}
			}
			else {
				std::cerr << "Screen Dimension is too small\n";
				exit(1);
			}
		}
		/** --demo will have two option, either --term or --tui */
		else if( strncmp( *( argv + 1 ), "--demo", 6 ) == 0 ) {
			if( argc < 3 ) {
				print_help();
				exit(1);
			}
			else {
				if( strncmp( *( argv + 2 ), "--term", 6 )  == 0 ) {
					run_driver( "demo" );
					print_vec(data_avail_to_print);
					print_vec(gen_data_to_print);
					print_vec(fittest_schedule_to_print);
				}
				else if( strncmp( *( argv + 2 ), "--tui", 5 ) == 0 ) {
					bool is_valid = check_screen_dimensions();
					if( is_valid ) {
						run_driver( "demo" );
						int status = print_with_ncurses();
						if( -1 == status ) {
							print_vec( data_avail_to_print );
							print_vec( gen_data_to_print );
							print_vec( fittest_schedule_to_print );
						}
					}
					else {
						std::cerr << "Screen Dimension is too small\n";
						exit(1);
					}
				}
			}
		}
		/*else if (strncmp(*(argv + 1), "--term", 6) == 0) {
			run_driver();
			print_vec(data_avail_to_print);
			print_vec(gen_data_to_print);
			print_vec(fittest_schedule_to_print);
		}*/
	}
	else {
		print_help();
	}

	return 0;
}

void run_driver( std::string&& type ) {
	std::cout << "Generating time-table..." << std::endl;
	try {
		driver( std::move(type) );
	}
	catch(std::exception& e) {
		std::cout << e.what();
		std::cout << "Exiting Now!!!\n";
		exit(1);
	}
}

bool check_screen_dimensions() {
	bool status{ true };

	initscr();
	raw();
	curs_set(0);

	int x, y;
	getmaxyx( stdscr, y, x );
	std::cout << "( x, y ): " << x << ", " << y << '\n';
	if( y < 10 || x < 40 ) status = false;

	endwin();
	return status;
}

int print_with_ncurses() {
	/** start ncurses from here */

	std::vector<std::vector<std::string>> result_data(DSIZE);
	result_data[0] = std::move(data_avail_to_print);
	result_data[1] = std::move(gen_data_to_print);
	result_data[2] = std::move(fittest_schedule_to_print);

	std::vector<std::vector<std::string>::size_type> pheights(DSIZE);
	std::vector<std::vector<std::string>::size_type> pwidths(DSIZE);

	// you have to make data string in such a way that this should give a accurate number ( no extra 1000 )
	for (int i = 0; i < DSIZE; i++) pheights[i] = 100 + (result_data[i].size() * 2);

	for (int i = 0; i < DSIZE; i++) {
		std::for_each(result_data[i].begin(), result_data[i].end(), [&pwidths, &i](const std::string& str) {
					pwidths[i] = std::max(pwidths[i], str.size());
				});
		pwidths[i] += COLS;
	}

	/*for (const std::vector<std::string>::size_type& x: pheights) std::cout << x << ' ';
	std::cout << '\n';*/

	/*for (const std::vector<std::string>::size_type& x: pwidths) std::cout << x << ' ';
	std::cout << '\n';*/

	std::vector<util::WIN> wins(DSIZE);
	std::vector<PANEL*> panels(DSIZE);
	PANEL* top;

	/*if (initscr() == NULL) {
		std::cout << "Warning!!! Ncurses not supported\n";
		return -1;
	}*/
	initscr();
	cbreak();
	noecho();
#ifdef DEBUG_CURSES
	curs_set(1);
#else
	curs_set(0);
#endif
	keypad(stdscr, TRUE);
	start_color();  // add check here

	util::print_title_desc();  // in data.hpp

	init_pads(wins, pheights, pwidths);

	for (int i = 0; i < DSIZE; i++) panels[i] = new_panel(wins[i]._win);
	top = panels[0];

	write_data_to_pads(wins, result_data);

	prefresh(wins[0]._win, wins[0]._rpos, wins[0]._cpos, wins[0]._starty + 3,
			wins[0]._startx + 2, wins[0]._endy - 2, wins[0]._endx - 1);


	set_panel_userptr(panels[0], panels[1]);
	set_panel_userptr(panels[1], panels[2]);
	set_panel_userptr(panels[2], panels[0]);

	top_panel(panels[0]);
	update_panels();
	doupdate();

	mvprintw(LINES - 1, 4, "Press <tab> and <\\> key for tab cycle, and arrow keys to scroll(vertical and horizontal)[press 'q' to exit]");
	refresh();

	int ch{}, cur_win{};
#ifdef DEBUG_CURSES
	std::string info = "key pressed: " + std::to_string(ch) + ", cur_pad: " + std::to_string(cur_win)
			+ ", LINES: " + std::to_string(LINES) + ", COLS: " + std::to_string(COLS)
			+ ", rpos: " + std::to_string(wins[cur_win]._rpos) + ", cpos: " + std::to_string(wins[cur_win]._cpos);
	move(LINES - 2, 4);
	clrtoeol();
	mvprintw(LINES - 2, 4, info.c_str());
#endif
	bool clrpad = false;

	int height = wins[cur_win]._endy - wins[cur_win]._starty;
	int width = wins[cur_win]._endx - wins[cur_win]._startx;
	while ((ch = getch()) != 'q') {
		switch (ch) {
			case 9:
				top = (PANEL*)panel_userptr(top);
				top_panel(top);
				cur_win = (cur_win == DSIZE - 1) ? 0 : ++cur_win;
				if (!clrpad) {
					erase();
					clrpad = !clrpad;
				}
				break;
			case 92:
				top = (PANEL*)panel_userptr(top);
				bottom_panel(top);
				cur_win = (cur_win == 0) ? DSIZE - 1 : --cur_win;
				if (!clrpad) {
					erase();
					clrpad = !clrpad;
				}
				break;
			case 'k':
			case KEY_UP:
				if (wins[cur_win]._rpos > 0) wins[cur_win]._rpos--;
				break;
			case 'j':
			case KEY_DOWN:
				if (wins[cur_win]._rpos <= pheights[cur_win] - height) wins[cur_win]._rpos++;
				break;
			case (('u' & 0x1F)):
			case KEY_PPAGE:
				if (wins[cur_win]._rpos > 0) {
					if (wins[cur_win]._rpos < height - 2) wins[cur_win]._rpos = 0;
					else wins[cur_win]._rpos -= (height - 2);
				}
				break;
			case (('d' & 0x1F)):
			case KEY_NPAGE:
				if (wins[cur_win]._rpos <= pheights[cur_win] - height) {
					// refresh this logic when you have figured out the way of
					// getting correct pheights for result_data
					wins[cur_win]._rpos += (height - 2);
				}
				break;
			case 'h':
			case KEY_LEFT:
				if (wins[cur_win]._cpos > 0) wins[cur_win]._cpos--;
				break;
			case 'l':
			case KEY_RIGHT:
				{
					int width = wins[cur_win]._endx - wins[cur_win]._endy;
					if (wins[cur_win]._cpos <= pwidths[cur_win] - width + 2) wins[cur_win]._cpos++;
				}
				break;
			case 'b':
			case KEY_HOME:  // KEY_HOME not working
				if (wins[cur_win]._cpos > 0) {
					if (wins[cur_win]._cpos < width - 2) wins[cur_win]._cpos = 0;
					else wins[cur_win]._cpos -= (width - 2);
				}
				break;
			case 'w':
			case KEY_END:  // KEY_END not working
				if (wins[cur_win]._cpos <= pwidths[cur_win] - width + 2) {
					move(LINES - 3, 4);
					clrtoeol();
					if (wins[cur_win]._cpos > pwidths[cur_win] - width + 2) {
						wins[cur_win]._cpos = pwidths[cur_win] - width + 2;
					}
					else {
						wins[cur_win]._cpos += (width - 2); {}
					}
					refresh();
				}
				break;
			case 'g':
				if (wins[cur_win]._rpos > 0) wins[cur_win]._rpos = 0;
				break;
			case 'G':
				if (wins[cur_win]._rpos < pheights[cur_win] - height + 2)
					wins[cur_win]._rpos = pheights[cur_win] - height + 2;
				break;
			case 'B':
				if (wins[cur_win]._cpos > 0) wins[cur_win]._cpos = 0;
				break;
			case 'W':
				if (wins[cur_win]._cpos < pwidths[cur_win] - width + 2)
					wins[cur_win]._cpos = pwidths[cur_win] - width + 2;
				break;
			default:
				break;  // currently, can't think of anything to put here
		}
		if (clrpad) {
			util::print_title_desc();
			wins[cur_win].create_box();
		}
		prefresh(wins[cur_win]._win, wins[cur_win]._rpos, wins[cur_win]._cpos, wins[cur_win]._starty + 3,
				wins[cur_win]._startx + 2, wins[cur_win]._endy - 2, wins[cur_win]._endx - 1);
		print_tab_names(wins, cur_win);
		//mvprintw( LINES - 1, 4, "You're here" );
		//refresh();
		//getch();
		if (clrpad) {
			mvprintw(LINES - 1, 4, "Press <tab> and <\\> key for tab cycle, and arrow keys to scroll(vertical and horizontal)[press 'q' to exit]");
			clrpad = !clrpad;
		}
#ifdef DEBUG_CURSES
		info = "key pressed: " + std::to_string(ch) + ", cur_pad: " + std::to_string(cur_win)
			+ ", LINES: " + std::to_string(LINES) + ", COLS: " + std::to_string(COLS)
			+ ", rpos: " + std::to_string(wins[cur_win]._rpos) + ", cpos: " + std::to_string(wins[cur_win]._cpos);
		move(LINES - 2, 4);
		clrtoeol();
		mvprintw(LINES - 2, 4, info.c_str());
#endif
		update_panels();
		doupdate();
		refresh();
	}


	for (int i = 0; i < DSIZE; i++) {
		if (NULL != panels[i]) del_panel(panels[i]);
		//if (nullptr != wins[i]._win) delwin(wins[i]._win);
	}

	endwin();
	return 0;
}

/*void print_title_desc() {
	for (int i = 0; i < 5; i++) {
		move(i, (COLS - MAX_TITLE_LEN) / 2);
		clrtoeol();
	}
	mvprintw(0, (COLS - MAX_TITLE_LEN) / 2, "  __  _");
	mvprintw(1, (COLS - MAX_TITLE_LEN) / 2, " / /_(_)__ ____ ___ ");
	mvprintw(2, (COLS - MAX_TITLE_LEN) / 2, "/ __/ / _ `/ -_) _ \\ ");
	mvprintw(3, (COLS - MAX_TITLE_LEN) / 2, "\\__/_/\\_, /\\__/_//_/ ");
	mvprintw(4, (COLS - MAX_TITLE_LEN) / 2, "     /___/ ");

	std::string desc{"Time-Table generation using Genetic Algorithm"};
	move(6, (COLS - desc.size()) / 2);
	clrtoeol();
	mvprintw(6, (COLS - desc.size()) / 2, desc.c_str());
	refresh();
}*/

/** start from here tomorrow */
void init_pads(std::vector<util::WIN>& wins, const std::vector<std::vector<std::string>::size_type>& pheights,
		const std::vector<std::vector<std::string>::size_type>& pwidths) {
	//for (int i = 0; i < DSIZE; i++) init_win(wins[i], pheights[i], pwidths[i]);
	for (int i = 0; i < DSIZE; i++) wins[i].init_win(pheights[i], pwidths[i]);
	print_tab_names(wins, 0);
}

void write_data_to_pads(std::vector<util::WIN>& wins, const std::vector<std::vector<std::string>>& result_data) {
	for (int i = 0; i < DSIZE; i++) {
		std::vector<std::string>::const_iterator citer = result_data[i].cbegin();
		while (citer != result_data[i].cend()) {
			wprintw(wins[i]._win, (*citer).c_str());
			citer++;
		}
	}
}

/** currently not in use */
void write_to_pad(WINDOW* win, const std::vector<std::string>& vec_str) {
	std::vector<std::string>::const_iterator citer = vec_str.cbegin();
	for (; citer != vec_str.cend(); citer++)
		wprintw(win, (*citer).c_str());
}

void print_tab_names(std::vector<util::WIN>& wins, int cur_tab_num) {
	util::WIN& temp_win = wins[0];

	std::vector<std::string>::size_type n = tab_names.size();
	int d = 4;
	int x = temp_win._startx + d;
	int y = temp_win._starty + (temp_win._endy - temp_win._starty);
	for (int i = 0; i < n; i++) {
		if (i == cur_tab_num) attron(A_REVERSE);
		mvprintw(y, x, tab_names[i].c_str());
		if (i == cur_tab_num) attroff(A_REVERSE);
		x += (tab_names[i].size() + d);
	}
	refresh();
}

void print_help() {
	std::cout << "Help for tigen:\n\
	When \"no argument\" is provided, it will show this help.\n\
	Following are the extra arguments you can provide:\n\
		--tui  [--debug]      : show output in curses mode.\n\
		--demo [--tui/--term] : creates demo data from main data to show output.\n\
		--version             : Show version of tigen.\n\
		--help                : Show this help.\n\n\
	Key combinations to navigate through ncurses window:\n\
		<keys>                      <movement>\n\
	-> selection window:\n\
		<space>          : to select the entity\n\
		up/down arrow    : move to select items\n\
		<enter>          : to confirm your selection before proceeding further\n\
		q                : to go to next entity( type ), if pressed again then exits the program\n\
	-> result window:\n\
		tab              : go to next tab(clockwise movement)\n\
		(back-slash)<\\>  : go to previous tab(anti-clockwise moment)\n\
		g                : move to top-most line in result window(vertical)\n\
		G                : move to bottom-most line in result window(vertical)\n\
		B                : move to begin of the current result window(horiontal)\n\
		W                : move to end of the current result window(horizontal)\n\
		h/left arrow     : move left(by 4 char)\n\
		l/right arrow    : move right(by 4 char)\n\
		k/up arrow       : move up(one row at a time)\n\
		l/down arrow     : move down(one row at a time)\n\
		<C-u>/PageUp     : move upon one screen view\n\
		<C-d>/PageDown   : move down one screen view)\n\
		b/Home           : move one screen view left\n\
		w/End            : move one screen view right\n";
}







	/*std::cout << "Generating time-table...\n"; std::thread th1 = std::thread([]() { std::cout << std::string({"Generation number: " + std::to_string(generation_number)});
			});
	std::thread th2 = std::thread([]() {
				driver();
			});

	th1.join();
	th2.join();
*/