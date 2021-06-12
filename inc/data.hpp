// header file

#ifndef _GUARD_DATA_HPP_
#define _GUARD_DATA_HPP_

#include "../inc/department.hpp"
#include "../inc/course.hpp"
#include "../inc/instructor.hpp"
#include "../inc/room.hpp"
#include "../inc/class_time.hpp"

#include <vector>
#include <string>

extern const size_t DEMO_DEPTS_SIZE;
extern const size_t DEMO_COURSES_SIZE;
extern const size_t DEMO_INSTRUCTORS_SIZE;
extern const size_t DEMO_ROOMS_SIZE;
extern const size_t DEMO_CLASS_TIMES_SIZE;

namespace gen_algo {
	class data {   // <-- PARENT CLASS
		//private:
			//void create_data();
		protected:
			std::vector<entities::department> _depts;
			std::vector<entities::course> _courses;
			std::vector<entities::instructor> _instructors;
			std::vector<entities::room> _rooms;
			std::vector<entities::class_time> _class_times;
			size_t _classes_count;
		public:
			data();
			void create_data();
			// accessors
			std::vector<entities::department> get_deparatments() const;
			std::vector<entities::course> get_courses() const;
			std::vector<entities::instructor> get_instructors() const;
			std::vector<entities::room> get_rooms() const;
			std::vector<entities::class_time> get_class_times() const;
			size_t get_classes_count() const;
	};

	class selection_data: public data {  // <-- CHILD1 CLASS
		public:
			explicit selection_data( const data* data );

	};

	class demo_data: public data {  // <-- CHILD2 CLASS
		public:
			explicit demo_data( const data* data );
	};
};

#endif