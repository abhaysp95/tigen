// main file

#include "../inc/driver.hpp"

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

#define VERSION 1.1

std::vector<std::string> new_lines;

void run_driver();
void print_help();
int print_with_ncurses();
void write_to_pad(WINDOW* win, const std::vector<std::string>& vec_str);

template <typename T>
void print_vec(const std::vector<T>& vec) {
	for (const T& x: vec)
		std::cout << x << '\n';
}

int main(int argc, char** argv) {
	if (argc == 2) {
		if (strncmp(*(argv + 1), "--term", 6) == 0) {
			run_driver();
			print_vec(data_avail_to_print);
			print_vec(gen_data_to_print);
			print_vec(fittest_schedule_to_print);
		}
		else if (strncmp(*(argv + 1), "--help", 6) == 0) {
			print_help();
		}
		else if (strncmp(*(argv + 1), "--version", 9) == 0) {
			std::cout << "tigen-" << VERSION << '\n';
		}
	}
	else {
		run_driver();
		int status = print_with_ncurses();
		if (status == -1) {
			print_vec(data_avail_to_print);
			print_vec(gen_data_to_print);
			print_vec(fittest_schedule_to_print);
		}
	}

	return 0;
}

void run_driver() {
	std::cout << "Generating time-table...\n";
	try {
		driver();
	}
	catch(std::exception& e) {
		std::cout << e.what();
		std::cout << "Exiting Now!!!\n";
		exit(1);
	}
}

int print_with_ncurses() {
	/** start ncurses from here */

	WINDOW* pad;
	size_t pad_height{}, pad_width{0};
	pad_height = data_avail_to_print.size()
		+ gen_data_to_print.size()
		+ fittest_schedule_to_print.size();
	pad_height *= 2;

	/** max width could only be from gen_data_to_print */
	std::for_each(gen_data_to_print.begin(), gen_data_to_print.end(), [&pad_width](const std::string& str) {
				pad_width = std::max(pad_width, str.size());
			});
	pad_width += 10;

	//std::cout << "pad_height & pad_width: " << pad_height << ", " << pad_width << '\n';

	if (initscr() == NULL) {
		std::cout << "Warning!!! Ncurses not supported\n";
		return -1;
	}
	cbreak();
	noecho();
	curs_set(0);
	start_color();  // add check here

	pad = newpad(pad_height, pad_width);
	keypad(pad, TRUE);

	new_lines.resize(4, std::string("\n"));

	// write all three data
	write_to_pad(pad, data_avail_to_print);
	write_to_pad(pad, new_lines);
	write_to_pad(pad, gen_data_to_print);
	write_to_pad(pad, new_lines);
	write_to_pad(pad, fittest_schedule_to_print);

	size_t pad_posy{}, pad_posx{};
	prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);

	int ch{};
	while ((ch = wgetch(pad)) != 'q') {
		switch (ch) {
			case 'k':
			case KEY_UP:
				if (pad_posy > 0) {
					pad_posy--;
					prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);
				}
				break;
			case 'j':
			case KEY_DOWN:
				if (pad_posy < pad_height) {
					pad_posy++;
					prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);
				}
				break;
			case (('u' & 0x1F)):
			case KEY_PPAGE:
				if (pad_posy > 0) {
					if (pad_posy > LINES)
						pad_posy -= (LINES - 1);
					else
						pad_posy = 0;
					prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);
				}
				break;
			case (('d' & 0x1F)):
			case KEY_NPAGE:
				if (pad_posy < pad_height) {
					pad_posy += (LINES - 1);
					prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);
				}
				break;
			case 'h':
			case KEY_LEFT:
				if (pad_posx > 0) {
					if (pad_posx < 4)
						pad_posx = 0;
					else
						pad_posx -= 4;
					prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);
				}
				break;
			case 'l':
			case KEY_RIGHT:
				if (pad_posx < (pad_width - COLS)) {
					pad_posx += 4;
					prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);
				}
				break;
			case 'b':
			case KEY_HOME:  // KEY_HOME not working
				if (pad_posx > 0) {
					if (pad_posx > COLS)
						pad_posx -= (COLS - 1);
					else
						pad_posx = 0;
					prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);
				}
				break;
			case 'w':
			case KEY_END:  // KEY_END not working
				if (pad_posx < (pad_width - COLS)) {
					if ((pad_width - pad_posx) > COLS) {
						if ((pad_posx + COLS) > (pad_width - COLS))
							pad_posx += (pad_width - pad_posx - COLS);
						else
						pad_posx += (COLS - 1);
						prefresh(pad, pad_posy, pad_posx, 0, 0, LINES - 1, COLS - 1);
					}
				}
				break;
		}
	}

	delwin(pad);
	endwin();
	return 0;
}


void write_to_pad(WINDOW* win, const std::vector<std::string>& vec_str) {
	std::vector<std::string>::const_iterator citer = vec_str.cbegin();
	for (; citer != vec_str.cend(); citer++)
		wprintw(win, (*citer).c_str());
}

void print_help() {
	std::cout << "Help for tigen:\n\
	When \"no argument\" is provided, it will run the algorithm and will show the output using ncurses.\n\
	Following are the extra arguments you can provide:\n\
		--term            : Run algo and print output in terminal.\n\
		--version         : Show version of tigen.\n\
		--help            : Show this help.\n\n\
	Key combinations to navigate through ncurses window:\n\
		  <keys>                      <movement>\n\
		h/left arrow           : move left(by 4 char)\n\
		l/right arrow          : move right(by 4 char)\n\
		k/up arrow             : move up(one row at a time)\n\
		l/down arrow           : move down(one row at a time)\n\
		<C-u>/PageUp           : move upon one screen view\n\
		<C-d>/PageDown         : move down one screen view)\n\
		b/Home                 : move one screen view left\n\
		w/End                  : move one screen view right\n";
}







	/*std::cout << "Generating time-table...\n"; std::thread th1 = std::thread([]() { std::cout << std::string({"Generation number: " + std::to_string(generation_number)});
			});
	std::thread th2 = std::thread([]() {
				driver();
			});

	th1.join();
	th2.join();
*/