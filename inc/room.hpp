// header file

#ifndef _GUARD_ROOM_HPP_
#define _GUARD_ROOM_HPP_

#include <string>

namespace entities {
	/**
	  this class is copyable and not movable
	  move operations are implicitly deleted
	  */
	class room {
		private:
			std::string _id;
			std::string _name;
			size_t _capacity;
		public:
			room();
			explicit room(std::string id, std::string name, size_t capacity);

			// copy constructor and copy assignment
			room(const room& other) = default;
			room& operator=(const room& other) = default;

			// move constructor and move assignment
			room(room&& other) = default;
			room& operator=(room&& other) = default;

			bool operator==( const room& other ) const;
			bool operator<( const room& other ) const;

			std::string get_id() const;
			std::string get_name() const;
			size_t get_capacity() const;
	};
};

#endif