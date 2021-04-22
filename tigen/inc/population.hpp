// header file

#ifndef _GUARD_POPULATION_HPP_
#define _GUARD_POPULATION_HPP_

#include "../inc/data.hpp"
#include "../inc/schedule.hpp"

#include <vector>

namespace gen_algo {
	class population {
		private:
			std::vector<schedule> _schedules;
		public:
			explicit population(size_t size, data gene_data);
			const std::vector<schedule>& get_schedules() const;
			std::vector<schedule>& get_schedules();
			void sort_by_fitness();
	};
};

#endif