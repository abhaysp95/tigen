// cpp file for "extra/extra_util.hpp"

#include "../../inc/extras/extra_util.hpp"

#include <random>
#include <chrono>


namespace util {
	std::mt19937_64 rang(std::chrono::high_resolution_clock::now().time_since_epoch().count());


	int rngi(int lim) {
		std::uniform_int_distribution<int> uid(0, lim - 1);
		return uid(rang);
	}

	double rngr(double lim) {
		std::uniform_real_distribution<double> urd(0, lim - 1);
		return urd(rang);
	}

	/*int get_random_num(size_t upto) {
		int random = rand();
		return (random - (random / upto) * upto);
	}*/


	/** used to throw exception with msg name containing the name of missing entity type if found */
	entitity_not_found::entitity_not_found(): _msg{"Entity Not Found!!!\n"} {}
	entitity_not_found::entitity_not_found(std::string& msg): _msg{msg + "\n"} {}
	entitity_not_found::entitity_not_found(std::string&& msg): _msg{msg + "\n"} {}
	const char* entitity_not_found::what() const throw() {
		return this->_msg.c_str();
	}
};
