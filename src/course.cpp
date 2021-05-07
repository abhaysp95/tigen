// cpp file for "course.hpp"

#include "../inc/course.hpp"

#include <algorithm>

namespace entities {
	course::course(std::string number, std::string name,
					size_t max_students, std::vector<instructor>& instructors):
		_number{number}, _name{name}, _max_students(max_students), _instructors(instructors) {}
	course::course(std::string number, std::string name,
					size_t max_students, std::vector<instructor>&& instructors):
		_number{number}, _name{name}, _max_students(max_students), _instructors(instructors) {}

	template<typename T> struct TD;  // just to check auto decltype

	template<typename T>
	bool is_equal(std::vector<T> const &v1, std::vector<T> const &v2) {

		std::pair<typename std::vector<T>::const_iterator,
			typename std::vector<T>::const_iterator> ppair = std::mismatch(
					v1.begin(), v1.end(), v2.begin());
		//TD<decltype(ppair)> td;  <-- it'll give error, check err msg for type
		return (ppair.first == v1.cend() && ppair.second == v2.cend());
	}

	bool course::operator==(const course& other) const {
		bool res = true;
		if (this->_number != other.get_number())
			res = false;
		if (this->_name != other.get_name())
			res = false;
		if (this->_max_students != other.get_max_students())
			res = false;
		if (!is_equal(this->_instructors, other.get_instructors()))
			res = false;
		return res;
	}

	std::string course::get_number() const { return this->_number; }
	std::string course::get_name() const { return this->_name; }
	size_t course::get_max_students() const { return this->_max_students; }
	std::vector<instructor> course::get_instructors() const { return this->_instructors; }

	/*std::ostream& course::dump(std::ostream& os) const {
		return os << this->_name;
	}*/

	std::ostream& operator<<(std::ostream& os, const course& other) {
		return os << other.get_name();
	}
};