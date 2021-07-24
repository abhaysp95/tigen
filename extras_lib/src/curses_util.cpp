// cpp file for "extra/curses_util.hpp"

#include <extras/curses_util.hpp>

const int MAX_TITLE_LEN = 21;

namespace util {
	void WIN::init() {
		_win = nullptr;
		_startx = 0;
		_starty = 0;
		_endx = 0;
		_endy = 0;
		_rpos = 0;
		_cpos = 0;
		_win_border.bl = 0;
		_win_border.br = 0;
		_win_border.bs = 0;
		_win_border.ls = 0;
		_win_border.rs = 0;
		_win_border.tl = 0;
		_win_border.tr = 0;
		_win_border.ts = 0;
		_win_border.hls = 0;
		_win_border.hrs = 0;
		_win_border.hll = 0;
	}

	WIN::WIN() { this->init(); }

	WIN::WIN(int pheight, int pwidth) {
		init();
		_win = newpad(pheight, pwidth);
		keypad(_win, TRUE);
	}

	WIN::WIN(const WIN& rhs): _win{rhs._win}, _cpos{rhs._cpos}, _rpos{rhs._rpos}, _startx{rhs._startx},
		_starty{rhs._starty}, _endx{rhs._endx}, _endy{rhs._endy}, _win_border{rhs._win_border} {
			init();
	}

	WIN& WIN::operator=(const WIN& rhs) {
		WIN copy(rhs);
		std::swap(*this, copy);
		return *this;
	}

	WIN::WIN(WIN&& rhs): _win{rhs._win}, _cpos{rhs._cpos}, _rpos{rhs._rpos}, _startx{rhs._startx},
		_starty{rhs._starty}, _endx{rhs._endx}, _endy{rhs._endy}, _win_border{rhs._win_border} {
			init();
	}

	WIN& WIN::operator=(WIN&& rhs) {
		std::swap(_win, rhs._win);
		std::swap(_cpos, rhs._cpos);
		std::swap(_rpos, rhs._rpos);
		std::swap(_startx, rhs._startx);
		std::swap(_starty, rhs._starty);
		std::swap(_endx, rhs._endx);
		std::swap(_endy, rhs._endy);
		std::swap(_win_border, rhs._win_border);
		return *this;
	}

	WIN::~WIN() {
		if (nullptr != this->_win) {
			delwin(this->_win);
			this->_win = nullptr;
		}
	}

	void WIN::create_box() {
		int x, y, w, h;
		std::string box_title{"Resultant Data Window"};
		x = _startx;
		y = _starty;
		w = _endx - x;
		h = _endy - y;
		mvaddch(y, x, _win_border.tl);
		mvaddch(y, x + w, _win_border.tr);
		mvaddch(y + h, x, _win_border.bl);
		mvaddch(y + h, x + w, _win_border.br);
		mvaddch(y + 2, x, _win_border.hls);
		mvaddch(y + 2, x + w, _win_border.hrs);
		mvhline(y + 2, x + 1, _win_border.hll, w - 1);
		mvhline(y, x + 1, _win_border.ts, w - 1);
		mvhline(y + h, x + 1, _win_border.bs, w - 1);
		mvvline(y + 1, x, _win_border.ls, h - 1);
		mvvline(y + 1, x + w, _win_border.rs, h - 1);
		move(y + 1, (x - box_title.size()) / 2);
		mvprintw(y + 1, (w - box_title.size()) / 2, box_title.c_str());
		refresh();
	}

	void WIN::init_win( const int pheight, const int pwidth, const int startx, const int starty, const int endx, const int endy ) {
		this->_win = newpad(pheight, pwidth);
		this->_startx = 4;
		this->_starty = 9;
		this->_endx = COLS - 4;
		this->_endy = LINES - 4;

		this->_win_border.bl = ACS_LLCORNER;
		this->_win_border.br = ACS_LRCORNER;
		this->_win_border.bs = ACS_HLINE;
		this->_win_border.ls = ACS_VLINE;
		this->_win_border.rs = ACS_VLINE;
		this->_win_border.tl = ACS_ULCORNER;
		this->_win_border.tr = ACS_URCORNER;
		this->_win_border.ts = ACS_HLINE;
		this->_win_border.hls = ACS_LTEE;
		this->_win_border.hrs = ACS_RTEE;
		this->_win_border.hll = ACS_HLINE;

		this->create_box();
	}

	void print_title_desc() {
		clear();
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
	}

};
