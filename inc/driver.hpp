// header file

#ifndef _GUARD_DRIVER_HPP_
#define _GUARD_DRIVER_HPP_

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

#include <vector>
#include <string>

extern const int POPULATION_SIZE;
extern const double MUTATION_RATE;
extern const double CROSSOVER_RATE;
extern const int TOURNAMENT_SELECTION_SIZE;
extern const int NUMBER_OF_ELITE_SCHEDULES;

extern int schedule_number;
extern int generation_number;
extern gen_algo::data *gene_data;

extern std::vector<std::string> data_avail_to_print;
extern std::vector<std::string> fittest_schedule_to_print;
extern std::vector<std::string> gen_data_to_print;

int driver();
void print_available_data(gen_algo::data* d);
const std::string print_table_element(std::string t, const int& width, const char cfill=' ');
void print_schedule_as_table(gen_algo::schedule& sch);
double calculate_population(gen_algo::genetic_algo& ga, gen_algo::population** new_population);
void print_generation_table(gen_algo::population* new_population, double fittest_schedule_fitness);

#endif
