#ifndef _GUARD_CURSES_UTIL_HPP_
#define _GUARD_CURSES_UTIL_HPP_

#include <ncurses.h>
#include <string>

namespace util {
	class WIN {
		private:
			typedef struct win_border_struct {
				chtype ls, rs, ts, bs, tl, bl, tr, br, hls, hrs, hll;
			} WIN_BORDER;
		public:
			WINDOW* _win;
			int _cpos, _rpos, _startx, _starty, _endx, _endy;
			WIN_BORDER _win_border;
			void init();
		public:
			WIN();
			WIN(int pheight, int pwidth);
			WIN(const WIN& rhs);
			WIN& operator=(const WIN& rhs);
			WIN(WIN&& rhs);
			WIN& operator=(WIN&& rhs);
			~WIN();
			void create_box();
			void init_win(const int pheight, const int pwidth);
	};
};

#endif
