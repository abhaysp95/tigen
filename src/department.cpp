// cpp file for "department.hpp"

#include "../inc/department.hpp"

namespace entities {
	department::department(std::string name, std::vector<course>& courses):
		_name{name}, _courses{courses} {}
	department::department(std::string name, std::vector<course>&& courses):
		_name{name}, _courses{courses} {}

	template<typename T>
	bool is_equal(const std::vector<T>& v1, const std::vector<T>& v2) {
		std::pair<typename std::vector<T>::const_iterator,
			typename std::vector<T>::const_iterator> ppair = std::mismatch(
					v1.begin(), v1.end(), v2.begin());
		return (ppair.first == v1.cend() && ppair.second == v2.cend());
	}

	bool department::operator==(const department& other) const {
		bool res = true;
		if (this->_name != other.get_name())
			res = false;
		if (!is_equal(this->_courses, other.get_courses()))
			res = false;
		return res;
	}

	std::string department::get_name() const { return this->_name; }
	std::vector<course> department::get_courses() const { return this->_courses; }
};