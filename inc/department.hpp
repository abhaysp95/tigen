// header file

#ifndef _GUARD_DEPARTMENT_HPP_
#define _GUARD_DEPARTMENT_HPP_

#include "../inc/course.hpp"

#include <vector>
#include <string>

namespace entities {
	/**
	  this class is copyable and not movable
	  move operations are implicitly deleted
	  */
	class department {
		private:
			std::string _name;
			std::vector<course> _courses;
		public:
			explicit department(std::string name, std::vector<course>& courses);
			explicit department(std::string name, std::vector<course>&& courses);

			// copy constructor and copy assignment
			department(const department& other) = default;
			department& operator=(const department& other) = default;

			// move constructor and move assignment
			department(department&& other) = default;
			department& operator=(department&& other) = default;

			// accessors
			std::string get_name() const;
			std::vector<course> get_courses() const;

			bool operator==(const department& other) const;
	};
};

#endif