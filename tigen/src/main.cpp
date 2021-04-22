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

#include <iostream>
#include <vector>
#include <iomanip>

extern const int POPULATION_SIZE;
extern const double MUTATION_RATE;
extern const double CROSSOVER_RATE;
extern const int TOURNAMENT_SELECTION_SIZE;
extern const int NUMBER_OF_ELITE_SCHEDULES;

int schedule_number = 0;

template <typename T>
std::string print_vector(const std::vector<T>& vec) {
	std::string res{};
	res += "[";
	for (typename std::vector<T>::const_iterator citer = vec.cbegin(); citer != vec.cend(); ++citer) {
		res += citer->get_name();
		if (citer < vec.cend() - 1)
			res += ", ";
	}
	res += "]";
	return res;
}

void print_available_data(gen_algo::data& d) {
	std::cout << "Available Departments ===>\n";
	for (const entities::department& dept: d.get_deparatments()) {
		std::cout << "name: " << dept.get_name() << ", courses: " << print_vector(dept.get_courses()) << '\n';
	}

	std::cout << "\nAvailable Courses ===>\n";
	for (const entities::course& crs: d.get_courses()) {
		std::cout << "course #: " << crs.get_number() << ", name: " << crs.get_name()
			<< ", max students #: " << crs.get_max_students() << ", instructors: "
			<< print_vector(crs.get_instructors()) << '\n';
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

int main(int argc, char **argv) {
	// second run
	gen_algo::data gene_data;
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
	//gen_algo::schedule new_sch(gene_data);
	//std::cout << new_sch << std::endl;
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