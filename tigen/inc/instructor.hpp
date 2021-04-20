// header file

#ifndef _GUARD_INSTRUCTOR_HPP_
#define _GUARD_INSTRUCTOR_HPP_

#include <string>

namespace entities {
	/**
	  this class is copyable and not movable
	  move operations are implicitly deleted
	  */
	class instructor {
		private:
			std::string _id;
			std::string _name;
		public:
			explicit instructor(std::string id, std::string name);

			// copy constructor and copy assignment
			instructor(const instructor& other) = default;
			instructor& operator=(const instructor& other) = default;

			// move constructor and move assignment
			instructor(instructor&& other) = delete;
			instructor& operator=(instructor&& other) = delete;

			// accessors
			std::string get_id() const;
			std::string get_name() const;

			std::ostream& dump(std::ostream& os) const;
	};
};

#endif