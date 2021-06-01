#ifndef _GUARD_EXCEPTION_UTIL_HPP_
#define _GUARD_EXCEPTION_UTIL_HPP_

#include <vector>
#include <string>

namespace util {
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
