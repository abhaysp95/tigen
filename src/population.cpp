// cpp file for "population.hpp"

#include "../inc/population.hpp"

#include <algorithm>

namespace gen_algo {
	population::population(size_t size, data gene_data) {
		std::vector<schedule> ts;
		ts.reserve(size);
		this->_schedules = ts;
		for (size_t i = 0; i < size; ++i) {
			schedule ts(gene_data);
			this->_schedules.push_back(ts);
		}
	}

	const std::vector<schedule>& population::get_schedules() const { return this->_schedules; }
	std::vector<schedule>& population::get_schedules() { return this->_schedules; }

	void population::sort_by_fitness() {
		std::sort(this->_schedules.begin(), this->_schedules.end(),
				[](schedule s1, schedule s2) {
					return s1.get_fitness() > s2.get_fitness();
				});
	}
};