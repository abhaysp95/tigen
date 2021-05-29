#ifndef _GUARD_EXTRA_UTIL_HPP_
#define _GUARD_EXTRA_UTIL_HPP_

#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

namespace util {
	//int get_random_num(size_t upto);
	int rngi(int limit);
	double rngr(double limit);

	class entitity_not_found: public std::exception {
		private:
			std::string _msg;
		public:
			entitity_not_found();
			entitity_not_found(std::string& msg);
			entitity_not_found(std::string&& msg);
			virtual const char* what() const throw();
	};

};

#endif
