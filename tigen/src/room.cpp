// cpp file for "room.hpp"

#include "../inc/room.hpp"

namespace entities {
	room::room(std::string number, size_t capacity):
		_number{number}, _capacity(capacity) {}

	std::string room::get_number() const { return this->_number; }
	size_t room::get_capacity() const { return this->_capacity; }
};