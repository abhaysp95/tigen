// header file

#ifndef _GUARD_CLASS_TIME_HPP_
#define _GUARD_CLASS_TIME_HPP_

#include <string>

namespace entities {
	/**
	  this class is copyable and not movable
	  move operations are implicitly deleted
	  */
	class class_time {
		private:
			std::string _id;
			std::string _time;
		public:
			class_time();
			explicit class_time(std::string id, std::string time);

			// copy constructor and copy assignment
			class_time(const class_time& other) = default;
			class_time& operator=(const class_time& other) = default;

			// move constructor and move assignment
			class_time(class_time&& other) = default;
			class_time& operator=(class_time&& other) = default;

			bool operator==( const class_time& other ) const;
			bool operator<( const class_time& other ) const;

			// accessors
			std::string get_id() const;
			std::string get_time() const;
			std::string get_name() const;
	};
};

#endif