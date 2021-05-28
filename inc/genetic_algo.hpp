// header file

#ifndef _GUARD_GENETIC_ALGO_HPP_
#define _GUARD_GENETIC_ALGO_HPP_

#include "../inc/schedule.hpp"
#include "../inc/data.hpp"
#include "../inc/population.hpp"

#include <vector>

extern const int POPULATION_SIZE;
extern const double MUTATION_RATE;
extern const double CROSSOVER_RATE;
extern const int TOURNAMENT_SELECTION_SIZE;
extern const int NUMBER_OF_ELITE_SCHEDULES;

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