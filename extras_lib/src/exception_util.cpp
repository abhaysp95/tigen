// cpp file for "extra/exception_util.hpp"

#include <extras/exception_util.hpp>

namespace util {

	/** used to throw exception with msg name containing the name of missing entity type if found */
	entitity_not_found::entitity_not_found(): _msg{"Entity Not Found!!!\n"} {}
	entitity_not_found::entitity_not_found(std::string& msg): _msg{msg + "\n"} {}
	entitity_not_found::entitity_not_found(std::string&& msg): _msg{msg + "\n"} {}
	const char* entitity_not_found::what() const throw() {
		return this->_msg.c_str();
	}

};
