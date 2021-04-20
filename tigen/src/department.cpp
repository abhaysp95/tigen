// cpp file for "department.hpp"

#include "../inc/department.hpp"

namespace entities {
	department::department(std::string name, std::vector<course>& courses):
		_name{name}, _courses{courses} {}
	department::department(std::string name, std::vector<course>&& courses):
		_name{name}, _courses{courses} {}

	std::string department::get_name() const { return this->_name; }
	std::vector<course> department::get_courses() const { return this->_courses; }
};