// main file

#include "../inc/driver.hpp"

//#include "../inc/pprint/pprint.hpp"
//#include <pprint.hpp>

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
#include <stdexcept>
#include <thread>

template <typename T>
void print_vec(const std::vector<T>& vec) {
	for (const T& x: vec)
		std::cout << x << '\n';
}

int main(int argc, char** argv) {
	std::cout << "Generating time-table...\n";

	driver();

	print_vec(data_avail_to_print);
	std::cout << '\n';
	print_vec(gen_data_to_print);
	std::cout << '\n';
	print_vec(fittest_schedule_to_print);
}



	/*std::cout << "Generating time-table...\n";

	std::thread th1 = std::thread([]() {
				std::cout << std::string({"Generation number: " + std::to_string(generation_number)});
			});
	std::thread th2 = std::thread([]() {
				driver();
			});

	th1.join();
	th2.join();
*/