// header file

#ifndef _GUARD_CLASS_HPP_
#define _GUARD_CLASS_HPP_

#include "course.hpp"
#include "department.hpp"
#include "room.hpp"
#include "instructor.hpp"
#include "class_time.hpp"

#include <vector>
#include <string>

namespace entities {
	/**
	  this class is copyable and not movable
	  move operations are implicitly deleted
	  */
	class sec_class {
		private:
			size_t _id;
			entities::department _dept;
			entities::course _course;
			entities::room _room;
			entities::instructor _instructor;
			entities::class_time _class_time;
		public:
			//sec_class(size_t id, entities::department dept, entities::course course,
					//entities::room room, entities::instructor instructor,
					//entities::class_time class_time);

			sec_class(size_t id, entities::department dept, entities::course course);

			// copy constructor and copy assignment
			sec_class(const sec_class& other) = default;
			sec_class& operator=(const sec_class& other) = default;

			// move constructor and move assignment
			sec_class(sec_class&& other) = delete;
			sec_class& operator=(sec_class& other) = default;

			// mutators
			void set_room(entities::room& room);
			void set_instructor(entities::instructor& instructor);
			void set_class_time(entities::class_time& class_time);

			// accessor
			size_t get_id() const;
			entities::department get_department() const;
			entities::room get_room() const;
			entities::course get_course() const;
			entities::instructor get_instructor() const;
			entities::class_time get_class_time() const;

			//std::ostream& dump(std::ostream& os) const;
			friend std::ostream& operator<<(std::ostream& os, const sec_class& other);
	};
};

#endif