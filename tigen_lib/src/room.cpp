// cpp file for "room.hpp"

#include <elib/room.hpp>

namespace entities {
	room::room()
		: _id{}, _name{}, _capacity{} {  }
	room::room(std::string id, std::string name, size_t capacity)
		: _id{ id }, _name{ name }, _capacity{ capacity } {}

	bool room::operator==( const room& other ) const {
		return ((this->_id == other.get_id())
				&& ( this->_name == other.get_name() )
				&& (this->_capacity == other.get_capacity()));
	}

	bool room::operator<( const room& other ) const {
		return this->get_id() < other.get_id();
	}

	std::string room::get_id() const { return this->_id; }

	std::string room::get_name() const { return this->_name; }

	size_t room::get_capacity() const { return this->_capacity; }
};