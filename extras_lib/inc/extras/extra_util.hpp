#ifndef _GUARD_EXTRA_UTIL_HPP_
#define _GUARD_EXTRA_UTIL_HPP_

#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>

namespace util {

	extern std::mt19937_64 rang;

	int rngi(int limit);
	double rngr(double limit);

};

#endif
