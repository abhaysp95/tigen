// cpp file for "extras/extra_util.hpp"

#include <extras/extra_util.hpp>

namespace util {
	std::mt19937_64 rang(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	int rngi( int limit ) {
		std::uniform_int_distribution<int> uid( 0, limit - 1 );
		return uid( rang );
	}
	double rngr( double limit ) {
		std::uniform_real_distribution<double> urd( 0, limit - 1 );
		return urd( rang );
	}
};
