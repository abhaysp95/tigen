// cpp file for "instructor.hpp"

#include "../inc/instructor.hpp"

namespace entities {
	instructor::instructor(std::string id, std::string name):
		_id{id}, _name{name} {}

	std::string instructor::get_id() const { return this->_id; }
	std::string instructor::get_name() const { return this->_name; }

	std::ostream& instructor::dump(std::ostream& os) const {
		return os << this->_name;
	}
};