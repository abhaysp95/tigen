// header file

#ifndef _GUARD_COURSE_HPP_
#define _GUARD_COURSE_HPP_

#include "../inc/instructor.hpp"

#include <vector>
#include <string>

namespace entities {
	/**
	  this class is copyable and not movable
	  move operations are implicitly deleted
	  */
	class course {
		private:
			std::string _number;
			std::string _name;
			size_t _max_students;
			std::vector<instructor> _instructors;
		public:
			explicit course(std::string number, std::string name,
					size_t max_students, std::vector<instructor>& instructors);
			explicit course(std::string number, std::string name,
					size_t max_students, std::vector<instructor>&& instructors);

			// copy constructor and copy assignment
			course(const course& other) = default;
			course& operator=(const course& other) = default;

			// move constructor and move assignment
			course(course&& other) = default;
			course& operator=(course&& other) = default;

			// accessors
			std::string get_number() const;
			std::string get_name() const;
			size_t get_max_students() const;
			std::vector<instructor> get_instructors() const;

			bool operator==(const course& other) const;

			//std::ostream& dump(std::ostream& os) const;
			friend std::ostream& operator<<(std::ostream& os, const course& other);
	};
};

#endif