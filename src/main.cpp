// main file

#include "../inc/course.hpp"
#include "../inc/sec_class.hpp"
#include "../inc/instructor.hpp"
#include "../inc/room.hpp"
#include "../inc/department.hpp"
#include "../inc/class_time.hpp"
#include "../inc/data.hpp"
#include "../inc/genetic_algo.hpp"
#include "../inc/schedule.hpp"
#include "../inc/population.hpp"
#include "../inc/schedule.hpp"

//#include "../inc/pprint/pprint.hpp"
//#include <pprint.hpp>

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

extern const int POPULATION_SIZE;
extern const double MUTATION_RATE;
extern const double CROSSOVER_RATE;
extern const int TOURNAMENT_SELECTION_SIZE;
extern const int NUMBER_OF_ELITE_SCHEDULES;

int schedule_number = 0;
gen_algo::data gene_data;

template <typename T>
std::string print_vector(const std::vector<T>& vec) {
	std::string res{};
	res += "[";
	for (typename std::vector<T>::const_iterator citer = vec.cbegin(); citer != vec.cend(); ++citer) {
		if (vec.size() > 1)
			res += "\n    ";
		res += citer->get_name();
		if (citer < vec.cend() - 1)
			res += ", ";
	}
	if (vec.size() > 1)
		res += '\n';
	res += "]";
	return res;
}

void print_available_data(gen_algo::data& d) {
	std::cout << "Available Departments ===>\n";
	for (const entities::department& dept: d.get_deparatments()) {
		std::cout << "name: " << dept.get_name() << ", courses: " << print_vector(dept.get_courses()) << '\n';
		//std::cout << "name: " << dept.get_name() << ", courses: ";
			//printer.print(dept.get_courses());
			//std::cout << '\n';
	}

	std::cout << "\nAvailable Courses ===>\n";
	for (const entities::course& crs: d.get_courses()) {
		std::cout << "course #: " << crs.get_number() << ", name: " << crs.get_name()
			<< ", max students #: " << crs.get_max_students() << ", instructors: "
			<< print_vector(crs.get_instructors()) << '\n';
		//printer.print(crs.get_instructors());
		//std::cout << '\n';
	}

	std::cout << "\nAvailabe Rooms ===>\n";
	for (const entities::room& room: d.get_rooms()) {
		std::cout << "room #: " << room.get_number() << ", seating capacity: " << room.get_capacity() << '\n';
	}

	std::cout << "\nAvailabe Instructors ===>\n";
	for (const entities::instructor& inst: d.get_instructors()) {
		std::cout << "id #: " << inst.get_id() << ", name: " << inst.get_name() << '\n';
	}

	std::cout << "\nClass Timings ===>\n";
	for (const entities::class_time& clstime: d.get_class_times()) {
		std::cout << "id #: " << clstime.get_id() << ", class time: " << clstime.get_time() << '\n';
	}

	std::cout << std::endl;
}

//template<typename T>
const std::string print_table_element(std::string t, const int& width) {
	std::cout << "I'm here at start\n";
	std::stringstream ss;
	ss << std::right << std::setw(width) << std::setfill(' ') << t;
	std::cout << "I'm here at end\n";
	return ss.str();
}

void print_schedule_as_table(gen_algo::schedule& sch, int gen_number) {
	size_t class_number{};

	std::cout << "done 0";
	std::vector<entities::sec_class> classes = sch.get_sec_classes();  // std::bad_alloc


	std::cout << "\n        ";
	std::cout << "Class # |            Department            | Course (number, max students #) | Room (capacity) \
		|   Instructor (id)   |    Meeting Time (ID)           ";
	std::cout << "------------------------------------------------------------------";
	std::cout << "------------------------------------------------------\n";
	for (const entities::sec_class& cls: classes) {
		std::cout << "done 1";

		// problem with const here
		std::vector<entities::department>::const_iterator citer_dept = std::find(
				gene_data.get_deparatments().cbegin(), gene_data.get_deparatments().cend(), cls.get_deparatment());
		std::cout << "done 2";
		std::vector<entities::course>::const_iterator citer_course  = std::find(
				gene_data.get_courses().cbegin(), gene_data.get_courses().cend(), cls.get_course());
		std::cout << "done 3";
		std::vector<entities::room>::const_iterator citer_room = std::find(
				gene_data.get_rooms().cbegin(), gene_data.get_rooms().cend(), cls.get_room());
		std::cout << "done 4";
		std::vector<entities::instructor>::const_iterator citer_instructor = std::find(
				gene_data.get_instructors().cbegin(), gene_data.get_instructors().cend(), cls.get_instructor());
		std::cout << "done 5";
		std::vector<entities::class_time>::const_iterator citer_class_time = std::find(
				gene_data.get_class_times().cbegin(), gene_data.get_class_times().cend(), cls.get_class_time());
		std::cout << "        ";
		std::cout << "done 6";
		//std::cout << print_table_element(class_number++, 7) << " | ";
		//std::cout << print_table_element(citer_dept->get_name(), 33) << " | ";
		//std::cout << print_table_element(citer_course->get_name(), 25) << " ("
			//<< citer_course->get_number() << ")" << " | ";
		//std::cout << print_table_element(citer_room->get_number(), 9) << " ("
			//<< citer_room->get_capacity() << ")" << " | ";
		//std::cout << print_table_element(citer_instructor->get_name(), 14) << " ("
			//<< citer_instructor->get_id() << ")" << " | ";
		//std::cout << print_table_element(citer_class_time->get_time(), 17) << " ("
			//<< citer_class_time->get_id() << ")";
	}
}

int main(int argc, char **argv) {
	// second run
	print_available_data(gene_data);

	// print a population
	size_t generation_number{};
	std::cout << "> Generation #  " << generation_number << '\n';
	std::cout << "  Schedule #  |            ";
	std::cout << "Classes[dept,class,room,instructor,class_time]   ";
	std::cout << "                  | Fitness | Conflicts \n";
	std::cout << "-----------------------------------------------------------";
	std::cout << "-----------------------------------------------------------\n";
	gen_algo::genetic_algo ga(gene_data);
	gen_algo::population new_population(POPULATION_SIZE, gene_data);
	new_population.sort_by_fitness();
	std::cout << std::fixed;
	std::cout << std::setprecision(5);
	for (gen_algo::schedule& sch: new_population.get_schedules()) {
		std::cout << "      " << schedule_number++ << "       | " << sch << " | "
			<< sch.get_fitness() << " | " << sch.get_number_of_conflicts() << '\n';
	}
	//print_schedule_as_table(new_population.get_schedules().at(0), generation_number);
	gen_algo::schedule new_sch(gene_data);
	std::cout << new_sch << std::endl;
	gen_algo::schedule sch = new_population.get_schedules().at(0);
	std::cout << "This is different\n";
	std::cout << sch << std::endl;
	std::vector<entities::sec_class> classes = sch.get_sec_classes();
	entities::sec_class cls = classes.at(3);
	std::cout << cls << std::endl;
	entities::course crs = cls.get_course();
	std::cout << crs.get_name() << std::endl;


	// std::find() or iterator idk, something is causing bad_alloc()
	//std::vector<entities::department>::const_iterator citer_dept = std::find(gene_data.get_deparatments().cbegin(), gene_data.get_deparatments().cend(), cls.get_deparatment());

	std::vector<entities::department>::size_type count{};
	for (const entities::department& dept: gene_data.get_deparatments()) {
		if (dept == cls.get_deparatment()) {
			// this above comparision checking is not correct, I think that's
			// why std::find() is also giving bad_alloc
			count++;  // this should be 4, but output is still 1
		}
	}

	std::cout << count << '\n' << std::endl;
	std::cout << gene_data.get_deparatments().at(count).get_name() << '\n' << std::endl;
	std::vector<entities::course>::const_iterator citer_course  = std::find(
			gene_data.get_courses().begin(), gene_data.get_courses().end(), cls.get_course());
	//entities::course crs = cls.get_course();

	//std::cout << print_table_element(citer_dept->get_name(), 33) << " | ";
	//std::cout << citer_dept->get_name() << std::endl;

	std::cout << gene_data.get_deparatments().at(0).get_name() << std::endl;
	return 0;
}







// old check(first run)


	/*entities::instructor i1("i1", "Chacha");
	entities::instructor i2("i2", "Mama");
	entities::instructor i3("i3", "Fufa");
	entities::instructor i4("i4", "Mausa");

	entities::room r1("r1", 30);
	entities::room r2("r2", 40);

	entities::class_time ct1("ct1", "9:00 - 10:00");
	entities::class_time ct2("ct2", "12:00 - 13:00");*/

	/* {  // using lvalues
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
	} */

	// using rvalues
	/*entities::course c1("c1", "kyu", 50, std::vector<entities::instructor>{i1, i2});
	entities::course c2("c2", "kaise", 42, std::vector<entities::instructor>{i2, i3});
	entities::course c3("c3", "kisliye", 54, std::vector<entities::instructor>{i3, i4});

	entities::department d1("kharab hai", std::vector<entities::course>{c1});
	entities::department d2("ye bhi kharab hai", std::vector<entities::course>{c2, c3});

	std::vector<entities::department> all_depts = {d1, d2};

	for (const entities::department& dept: all_depts) {
		std::cout << "Department: " << dept.get_name() << ", ";
		for (const entities::course& crs: dept.get_courses()) {
			std::cout << "Course: " << crs.get_name() << ", ";
			std::vector<entities::instructor> cur_inst = crs.get_instructors();
			for (std::vector<entities::instructor>::const_iterator citer = cur_inst.cbegin();
					citer != cur_inst.cend(); ++citer) {
				std::cout << "inst: " << citer->get_name();
				if (citer < cur_inst.cend() - 1) {
					std::cout << ", ";
				}
			}
			std::cout << std::endl;
		}
	}*/