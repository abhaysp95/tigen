// cpp file for "class.hpp"

#include <elib/sec_class.hpp>

namespace entities {
	//sec_class::sec_class(size_t id, entities::department dept, entities::course course,
					//entities::room room, entities::instructor instructor,
					//entities::class_time class_time):
		//_id{id}, _dept{dept}, _course{course}, _room{room},
		//_instructor{instructor}, _class_time{class_time} {}

	sec_class::sec_class(size_t id, entities::department dept, entities::course course):
		_id{id}, _dept{dept}, _course{course} {}

	void sec_class::set_room(entities::room& room) { this->_room = room; }
	void sec_class::set_instructor(entities::instructor& instructor) {
		this->_instructor = instructor;
	}
	void sec_class::set_class_time(entities::class_time& class_time) {
		this->_class_time = class_time;
	}

	size_t sec_class::get_id() const { return this->_id; }
	// try to return if you can, constant entities from below accessors
	entities::department sec_class::get_department() const { return this->_dept; }
	entities::course sec_class::get_course() const { return this->_course; }
	entities::room sec_class::get_room() const { return this->_room; }
	entities::instructor sec_class::get_instructor() const { return this->_instructor; }
	entities::class_time sec_class::get_class_time() const { return this->_class_time; }

	/*std::ostream& sec_class::dump(std::ostream& os) const {
		return os << ("[ " + this->_dept.get_name() + ", "
				+ this->_course.get_number() + ", "
				+ this->_room.get_number() + ", "
				+ this->_instructor.get_id() + ", "
				+ this->_class_time.get_id() + " ]");
	}*/

	std::ostream& operator<<(std::ostream& os, const sec_class& other) {
		return os << ("[ " + other.get_department().get_id() + ", "
				+ other.get_course().get_id() + ", "
				+ other.get_room().get_id() + ", "
				+ other.get_instructor().get_id() + ", "
				+ other.get_class_time().get_id() + " ]");
	}

};