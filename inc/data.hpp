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

namespace gen_algo {
	class data {
		private:
			std::vector<entities::department> _depts;
			std::vector<entities::course> _courses;
			std::vector<entities::instructor> _instructors;
			std::vector<entities::room> _rooms;
			std::vector<entities::class_time> _class_times;
			size_t _classes_count;
			//data* _instance;

			//data* get_instance();  // returning the instance as reference
			void create_data();
		public:
			data();
			// accessors
			std::vector<entities::department> get_deparatments() const;
			std::vector<entities::course> get_courses() const;
			std::vector<entities::instructor> get_instructors() const;
			std::vector<entities::room> get_rooms() const;
			std::vector<entities::class_time> get_class_times() const;
			size_t get_classes_count() const;
	};
};

#endif