// cpp file for "room.hpp"

#include "../inc/room.hpp"

namespace entities {
	room::room() {}
	room::room(std::string id, size_t capacity):
		_id{ id }, _capacity{ capacity } {}

	bool room::operator==(const room& other) const {
		return ((this->_id == other.get_id())
				&& (this->_capacity == other.get_capacity()));
	}

	std::string room::get_id() const { return this->_id; }
	size_t room::get_capacity() const { return this->_capacity; }
};