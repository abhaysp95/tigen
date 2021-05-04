// cpp file for "room.hpp"

#include "../inc/room.hpp"

namespace entities {
	room::room() {}
	room::room(std::string number, size_t capacity):
		_number{number}, _capacity(capacity) {}

	bool room::operator==(const room& other) const {
		return ((this->_number == other.get_number())
				&& (this->_capacity == other.get_capacity()));
	}

	std::string room::get_number() const { return this->_number; }
	size_t room::get_capacity() const { return this->_capacity; }
};