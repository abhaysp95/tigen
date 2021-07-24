// cpp file for "department.hpp"

#include <elib/department.hpp>

namespace entities {
	department::department( std::string id, std::string name )
		: _id{ id }, _name{ name } {  }
	department::department( std::string id, std::string name, const std::vector<course>& courses )
		: _id{ id }, _name{ name }, _courses{ courses } {  }
	department::department( std::string id, std::string name, std::vector<course>&& courses )
		: _id{ id }, _name{ name }, _courses{ std::move( courses ) } {  }

	template<typename T>
	bool is_equal(const std::vector<T>& v1, const std::vector<T>& v2) {
		std::pair<typename std::vector<T>::const_iterator,
			typename std::vector<T>::const_iterator> ppair = std::mismatch(
					v1.begin(), v1.end(), v2.begin());
		return (ppair.first == v1.cend() && ppair.second == v2.cend());
	}

	bool department::operator==(const department& other) const {
		bool res = true;
		if( this->_id != other.get_id() ) res = false;
		if (this->_name != other.get_name())
			res = false;
		if (!is_equal(this->_courses, other.get_courses()))
			res = false;
		return res;
	}

	void department::set_courses( const std::vector<course>& courses ) { this->_courses = courses; }
	void department::set_courses( std::vector<course>&& courses ) { this->_courses = std::move( courses ); }
	void department::set_instructor_for_course( const std::vector<instructor>& instructors, size_t crs_idx ) {
		if( 0 <= crs_idx && crs_idx < this->_courses.size() ) this->_courses[crs_idx].set_instructors( instructors );
	}

	std::string department::get_id() const { return this->_id; }
	std::string department::get_name() const { return this->_name; }
	std::vector<course> department::get_courses() const { return this->_courses; }
};