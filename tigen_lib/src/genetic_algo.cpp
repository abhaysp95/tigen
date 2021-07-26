// cpp file for "genetic_algo.hpp"

#include <glib/genetic_algo.hpp>
#include <extras/extra_util.hpp>

const int POPULATION_SIZE = 9;
const double MUTATION_RATE = 0.1;
const double CROSSOVER_RATE = 0.9;
const int TOURNAMENT_SELECTION_SIZE = 3;
const int NUMBER_OF_ELITE_SCHEDULES = 1;

namespace gen_algo {
	genetic_algo::genetic_algo(data gene_data): _gene_data{gene_data} {}

	population* genetic_algo::evolve(population* pop) {
		return this->mutate_population(this->crossover_population(pop));
	}

	population* genetic_algo::crossover_population(population* pop) {
		population* crs_pop = new population(pop->get_schedules().size(), this->_gene_data);

		for (size_t i = 0; i < NUMBER_OF_ELITE_SCHEDULES; ++i) {
			crs_pop->get_schedules()[i] = pop->get_schedules().at(i);
		}

		for (size_t i = NUMBER_OF_ELITE_SCHEDULES; i < pop->get_schedules().size(); ++i) {
			// if (CROSSOVER_RATE > (rand() / static_cast<double>(RAND_MAX))) {
			// reason for choosing 2.0 is that I want number which would be
			// above 0.0 and something close around 1.0 and 2.0 fits that
			// criteria
			if (CROSSOVER_RATE > util::rngr(2.0)) {
				//this->select_tournament_population(pop)->sort_by_fitness();
				population* trnmnt_pop1 = this->select_tournament_population(pop);
				trnmnt_pop1->sort_by_fitness();
				population* trnmnt_pop2 = this->select_tournament_population(pop);
				trnmnt_pop2->sort_by_fitness();
				//schedule sch1 = this->select_tournament_population(pop)->get_schedules().at(0);
				//schedule sch2 = this->select_tournament_population(pop)->get_schedules().at(0);
				schedule sch1 = trnmnt_pop1->get_schedules().at(0);
				schedule sch2 = trnmnt_pop2->get_schedules().at(0);
				// try deleting *trnmnt_pop here, since sch1 and sch2 are copied
				if (trnmnt_pop1)
					delete trnmnt_pop1;
				if (trnmnt_pop2)
					delete trnmnt_pop2;
				schedule* crs_sch = crossover_schedule(sch1, sch2);
				crs_pop->get_schedules()[i] = crs_sch;
				if (crs_sch)
					delete crs_sch;  // trying to free crs_sch here
			}
			else {
				crs_pop->get_schedules()[i] = pop->get_schedules().at(i);
			}
		}

		// I think, pop will also be not needed, so free that too
		if (pop)
			delete pop;
		return crs_pop;
	}

	schedule* genetic_algo::crossover_schedule(schedule& sch1, schedule& sch2) {
		schedule* sch = new schedule(this->_gene_data);
		size_t count_sec_classes = sch->get_sec_classes().size();

		for (size_t i = 0; i < count_sec_classes; ++i) {
			//if ((rand() / static_cast<double>(RAND_MAX)) > 0.5)
			if (util::rngr(2.0) > 0.5)
				sch->get_sec_classes()[i] = sch1.get_sec_classes().at(i);
			else
				sch->get_sec_classes()[i] = sch2.get_sec_classes().at(i);
		}

		return sch;
	}

	population* genetic_algo::mutate_population(population* pop) {
		population* mutate_population = new population(pop->get_schedules().size(), this->_gene_data);
		std::vector<schedule>& schedules = mutate_population->get_schedules();

		for (size_t i = 0; i < NUMBER_OF_ELITE_SCHEDULES; ++i) {
			schedules[i] = pop->get_schedules().at(i);
		}

		for (size_t i = NUMBER_OF_ELITE_SCHEDULES; i < pop->get_schedules().size(); ++i) {
			mutate_schedule(pop->get_schedules().at(i));
			schedules[i] = pop->get_schedules().at(i);
		}

		// now, there's no need for this *pop, delete it after calling this mutate_population
		if (pop)
			delete pop;
		return mutate_population;
	}

	void genetic_algo::mutate_schedule(schedule& sch) {
		schedule tsch(this->_gene_data);

		for (size_t i = 0; i < sch.get_sec_classes().size(); ++i) {
			//if (MUTATION_RATE > (rand() / static_cast<double>(RAND_MAX)))
			if (MUTATION_RATE > util::rngr(1.5))
				sch.get_sec_classes()[i] = tsch.get_sec_classes().at(i);
		}

	}

	population* genetic_algo::select_tournament_population(population* pop) {
		population* tournament_population = new population(TOURNAMENT_SELECTION_SIZE, this->_gene_data);

		for (size_t i = 0; i < TOURNAMENT_SELECTION_SIZE; ++i) {
			tournament_population->get_schedules()[i] = pop->get_schedules()[
				util::rngi( pop->get_schedules().size() ) ];
				//util::rngr( pop->get_schedules().size() ) ];
		}

		return tournament_population;
	}
};