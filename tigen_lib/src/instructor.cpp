// cpp file for "instructor.hpp"

#include <elib/instructor.hpp>

namespace entities {
	instructor::instructor()
		: _id{}, _name{} {  }
	instructor::instructor(std::string id, std::string name)
		: _id{id}, _name{name} {  }

	bool instructor::operator==( const instructor& other ) const {
		return ((this->_id == other.get_id())
				&& (this->_name == other.get_name()));
	}

	bool instructor::operator<( const instructor& other ) const {
		return this->get_id() < other.get_id();
	}

	std::string instructor::get_id() const { return this->_id; }
	std::string instructor::get_name() const { return this->_name; }

	/*std::ostream& instructor::dump(std::ostream& os) const {
		return os << this->_name;
	}*/

	std::ostream& operator<<(std::ostream& os, const instructor& other) {
		return os << other.get_name();
	}
};