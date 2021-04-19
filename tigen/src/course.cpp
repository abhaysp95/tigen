// cpp file for "course.hpp"

#include "../inc/course.hpp"

namespace entities {
	course::course(std::string number, std::string name,
					size_t max_students, std::vector<instructor> instructors):
		_number{number}, _name{name}, _max_students(max_students), _instructors(instructors) {}

	std::string course::get_number() const { return this->_number; }
	std::string course::get_name() const { return this->_name; }
	size_t course::get_max_students() const { return this->_max_students; }
	std::vector<instructor> course::get_instructors() const { return this->_instructors; }

	std::ostream& course::dump(std::ostream& os) const {
		return os << this->_name;
	}
};