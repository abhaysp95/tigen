// cpp file for "class_time.hpp"

#include "../inc/class_time.hpp"

namespace entities {
	class_time::class_time(std::string id, std::string time):
		_id{id}, _time{time} {}

	std::string class_time::get_id() const { return this->_id; }
	std::string class_time::get_time() const { return this->_time; }
};