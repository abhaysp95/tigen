// header file

#ifndef _GUARD_GENETIC_ALGO_HPP_
#define _GUARD_GENETIC_ALGO_HPP_

#include "../inc/schedule.hpp"
#include "../inc/data.hpp"
#include "../inc/population.hpp"

#include <vector>

const int POPULATION_SIZE = 9;
const double MUTATION_RATE = 0.1;
const double CROSSOVER_RATE = 0.9;
const int TOURNAMENT_SELECTION_SIZE = 3;
const int NUMBER_OF_ELITE_SCHEDULES = 1;

namespace gen_algo {
	class genetic_algo {
		private:
			data _gene_data;
		public:
			explicit genetic_algo(data gene_data);

			population* evolve(population* pop);
			population* crossover_population(population* pop);
			schedule* crossover_schedule(schedule& sch1, schedule& sch2);
			population* mutate_population(population* pop);
			void mutate_schedule(schedule& sch);
			population* select_tournament_population(population* pop);
	};
};

#endif