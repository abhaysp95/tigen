// main file

#include "../inc/course.hpp"
#include "../inc/sec_class.hpp"
#include "../inc/instructor.hpp"
#include "../inc/room.hpp"
#include "../inc/department.hpp"
#include "../inc/class_time.hpp"

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
	entities::instructor i1("i1", "Chacha");
	entities::instructor i2("i2", "Mama");
	entities::instructor i3("i3", "Fufa");
	entities::instructor i4("i4", "Mausa");

	entities::room r1("r1", 30);
	entities::room r2("r2", 40);

	entities::class_time ct1("ct1", "9:00 - 10:00");
	entities::class_time ct2("ct2", "12:00 - 13:00");

	std::vector<entities::instructor> iset1 = {i1, i2};
	std::vector<entities::instructor> iset2 = {i2, i3};
	std::vector<entities::instructor> iset3 = {i3, i4};
	entities::course c1("c1", "kyu", 50, iset1);
	entities::course c2("c2", "kaise", 42, iset2);
	entities::course c3("c3", "kisliye", 54, iset3);

	// make this type of constructor too
	//entities::course c1("c1", "kyu", 50, std::vector<entities::instructor>(i1, i2));

	std::vector<entities::course> dset1 = {c1};
	std::vector<entities::course> dset2 = {c2, c3};
	entities::department d1("kharab hai", dset1);
	entities::department d2("ye bhi kharab hai", dset2);

	std::vector<entities::department> all_depts = {d1, d2};

	for (const entities::department& dept: all_depts) {
		std::cout << "Department: " << dept.get_name() << ", ";
		for (const entities::course& crs: dept.get_courses()) {
			std::cout << "Course: " << crs.get_name() << ", ";
			for (const entities::instructor& inst: crs.get_instructors()) {
				std::cout << "inst: " << inst.get_name() << "\n";
			}
		}
	}

	std::cout << std::endl;
	return 0;
}