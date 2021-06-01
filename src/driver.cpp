// cpp file for "driver.hpp"

#include "../inc/driver.hpp"
#include "../inc/extras/extra_util.hpp"
#include "../inc/extras/exception_util.hpp"

#include <iostream>
#include <ios>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include <cstdlib>
#include <cxxabi.h>
#include <random>
#include <chrono>
#include <exception>
#include <stdexcept>

int schedule_number = 0;
int generation_number = 0;
gen_algo::data *gene_data;

std::vector<std::string> data_avail_to_print;
std::vector<std::string> fittest_schedule_to_print;
std::vector<std::string> gen_data_to_print;

template <typename T>
std::string vec_to_str(const std::vector<T>& vec) {
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
	res += "]\n";
	return res;
}

void print_available_data(gen_algo::data* d) {
	data_avail_to_print.reserve(10);

	data_avail_to_print.push_back("Available Departments ===>\n");
	for (const entities::department& dept: d->get_deparatments())
		data_avail_to_print.push_back(std::string{"name: "
				+ dept.get_name()
				+ ", courses: "
				+ vec_to_str(dept.get_courses())});

	data_avail_to_print.push_back("\n");
	data_avail_to_print.push_back("Available Courses ===>\n");
	for (const entities::course& crs: d->get_courses())
		data_avail_to_print.push_back(std::string{"course #: " + crs.get_number()
				+ ", name: " + crs.get_name()
				+ ", max students #: " + std::to_string(crs.get_max_students())
				+ ", instructors: " + vec_to_str(crs.get_instructors())});

	data_avail_to_print.push_back("\n");
	data_avail_to_print.push_back("Availabe Rooms ===>\n");
	for (const entities::room& room: d->get_rooms())
		data_avail_to_print.push_back("room #: " + room.get_number()
				+ ", seating capacity: " + std::to_string(room.get_capacity()) + "\n");

	data_avail_to_print.push_back("\n");
	data_avail_to_print.push_back("Availabe Instructors ===>\n");
	for (const entities::instructor& inst: d->get_instructors())
		data_avail_to_print.push_back(std::string{"id #: " + inst.get_id()
				+ ", name: " + inst.get_name()} + "\n");

	data_avail_to_print.push_back("\n");
	data_avail_to_print.push_back("Class Timings ===>\n");
	for (const entities::class_time& clstime: d->get_class_times())
		data_avail_to_print.push_back(std::string{"id #: " + clstime.get_id()
				+ ", class time: " + clstime.get_time()} + "\n");
}

const std::string print_table_element(std::string t, const int& width, const char cfill) {
	std::stringstream ss;
	ss << std::right << std::setw(width) << std::setfill(cfill) << t;
	return ss.str();
}

template<typename T>
void free_obj(T* object) {
	if (object) {
		delete object;
		object = nullptr;
	}
}


// return demangled type name of template typename
// I should probably remove this(cause, it's compiler specific thing and would
// give wrong results if user uses some other compilers)
template<typename T>
std::string type_name() {
	int status{};
	std::string tname = typeid(T).name();
	#if defined(__clang__) || defined(_GNUG__)
	char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
	if (status == 0) {
		tname = demangled_name;
		std::free(demangled_name);
	}
	#else
	std::cout << "\ndemangling status: " << status << '\n';
	std::cout <<
		"Type Name demangling is not supported by Compiler[variable \"__clang__\" and \"__GNUG__\" undefined]\n";
	#endif
	return tname;
}

template<typename T>
void entity_existance_check(const std::vector<T>& from_entity,
		const typename std::vector<T>::const_iterator& check_entity) {
	if (check_entity == from_entity.cend()) {
		std::string msg = type_name<T>() + " not found!!!\n";
		throw util::entitity_not_found(std::move(msg));
	}
}

void print_schedule_as_table(gen_algo::schedule& sch) {
	size_t class_number{};
	std::vector<entities::sec_class> classes = sch.get_sec_classes();  // std::bad_alloc

	std::vector<entities::sec_class>::size_type res_size = classes.size();
	fittest_schedule_to_print.reserve(res_size + 2);

	fittest_schedule_to_print.push_back("\n");
	fittest_schedule_to_print.push_back(std::string{print_table_element(" ", 8)
		+ print_table_element("Class #", 7) + " | "
		+ print_table_element("Department", 33) + " | "
		+ print_table_element("Course (#, max students #)", 31) + " | "
		+ print_table_element("Room (capacity)", 15) + " | "
		+ print_table_element("Instructor (id)", 20) + " | "
		+ print_table_element("Meeting Time (id)", 23)} + "\n");

	fittest_schedule_to_print.push_back(print_table_element(" ", 8)
			+ print_table_element(" ", 145, '-') + "\n");

	/** Question: Are these iterators really needed ?  Confirm with classes */

	for (const entities::sec_class& cls: classes) {
		std::vector<entities::department> vtdept = gene_data->get_deparatments();
		std::vector<entities::department>::const_iterator citer_dept = std::find(
				vtdept.cbegin(), vtdept.cend(), cls.get_deparatment());
		entity_existance_check(vtdept, citer_dept);

		std::vector<entities::course> vtcrs = gene_data->get_courses();
		std::vector<entities::course>::const_iterator citer_course  = std::find(
				vtcrs.cbegin(), vtcrs.cend(), cls.get_course());
		entity_existance_check(vtcrs, citer_course);

		std::vector<entities::room> vtroom = gene_data->get_rooms();
		std::vector<entities::room>::const_iterator citer_room = std::find(
				vtroom.cbegin(), vtroom.cend(), cls.get_room());
		entity_existance_check(vtroom, citer_room);

		std::vector<entities::instructor> vtinst = gene_data->get_instructors();
		std::vector<entities::instructor>::const_iterator citer_instructor = std::find(
				vtinst.cbegin(), vtinst.cend(), cls.get_instructor());
		entity_existance_check(vtinst, citer_instructor);

		std::vector<entities::class_time> vtctime = gene_data->get_class_times();
		std::vector<entities::class_time>::const_iterator citer_class_time = std::find(
				vtctime.cbegin(), vtctime.cend(), cls.get_class_time());
		entity_existance_check(vtctime, citer_class_time);

		// don't use numbers here (get max for each / or maybe print in a way, where you don't need it)


		// add generic exception handling here ( do cleanup here too )

		fittest_schedule_to_print.push_back(print_table_element(" ", 8)
			+ print_table_element(std::to_string(++class_number), 7) + " | "
			+ print_table_element(citer_dept->get_name(), 33) + " | "
			+ print_table_element(std::string(citer_course->get_name() +
					" (" + citer_course->get_number() + ')'), 31) + " | "
			+ print_table_element(std::string(citer_room->get_number() +
					" (" + std::to_string(citer_room->get_capacity()) + ')'), 15) + " | "
			+ print_table_element(std::string(citer_instructor->get_name() +
					" (" + citer_instructor->get_id() + ')'), 20) + " | "
			+ print_table_element(std::string(citer_class_time->get_time() +
					" (" + citer_class_time->get_id() + ')'), 23) + "\n");

	}
}

/** if there's no population yet, make new, else evolve the population for next
 * generation */
double calculate_population(gen_algo::genetic_algo& ga, gen_algo::population** new_population) {
	double fittest_schedule_fitness{};

	if ((*new_population) == nullptr)
		*new_population = new gen_algo::population(POPULATION_SIZE, *gene_data);
	else
		*new_population = ga.evolve(*new_population);
	(*new_population)->sort_by_fitness();
	std::vector<gen_algo::schedule>& np_schedules = (*new_population)->get_schedules();
	gen_algo::schedule& fittest_schedule = np_schedules.at(0);

	fittest_schedule_fitness = fittest_schedule.get_fitness();
	return fittest_schedule_fitness;
}

void print_generation_table(gen_algo::population* new_population, double fittest_schedule_fitness) {
	std::stringstream ss;

	//gen_data_to_print.reserve(32);  // give a thought to this number

	gen_data_to_print.push_back("\n");
	ss << "> Generation #  " << ++generation_number << '\n';
	ss << "  Schedule #  ";
	ss << "| Fitness | Conflicts | ";
	ss << "                  Classes[dept,class,room,instructor,class_time]   \n";
	ss << std::setw(750) << std::setfill('-') << '\n';
	//ss << "-----------------------------------------------------------";
	//ss << "-----------------------------------------------------------\n";
	gen_data_to_print.push_back(ss.str());
	ss.str(std::string());

	// can you make this better ? (clearing and copying ss everytime)

	schedule_number = 0;
	for (gen_algo::schedule& sch: new_population->get_schedules()) {
		ss << std::fixed;
		ss << std::setprecision(5);
		ss << "      " << ++schedule_number << "       | ";
		ss << sch.get_fitness() << " | " << std::right << std::setw(9) << std::setfill(' ') << sch.get_number_of_conflicts();
		ss << " | " << sch << '\n';
		gen_data_to_print.push_back(ss.str());
		ss.str(std::string());
	}
}

int driver() {
	// set the seed
	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	//int x = func(10);  // just for test
	//std::cout << "x is " << x << '\n';

	// comment these if you are going to use C based input/output methods
	//std::ios_base::sync_with_stdio(false);
	//std::cin.tie(NULL);
	//std::cout.tie(NULL);

	gene_data = new gen_algo::data;
	print_available_data(gene_data);

	gen_algo::genetic_algo ga(*gene_data);
	gen_algo::population *new_population = nullptr;
	double fittest_schedule_fitness{};

	/** do calculation and print generation */
	do {
		fittest_schedule_fitness = calculate_population(ga, &new_population);
		print_generation_table(new_population, fittest_schedule_fitness);
		std::cout << "Generation Number " << generation_number << " generated!!!\n";
	} while (fittest_schedule_fitness < 1.0);

	try {
		std::vector<gen_algo::schedule>& np_schedules = new_population->get_schedules();
		gen_algo::schedule& fittest_schedule = np_schedules.at(0);
		print_schedule_as_table(fittest_schedule);
	}
	catch (util::entitity_not_found& e) {
		free_obj(new_population);
		free_obj(gene_data);
		throw;
	}

	free_obj(new_population);
	free_obj(gene_data);
	return 0;
}
