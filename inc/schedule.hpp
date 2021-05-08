// header file

#ifndef _GUARD_SCHEDULE_HPP_
#define _GUARD_SCHEDULE_HPP_

#include "../inc/data.hpp"
#include "../inc/sec_class.hpp"

#include <vector>

namespace gen_algo {
	class schedule {
		private:
			bool _is_fitness_changed;
			double _fitness;
			size_t _sec_class_number;
			size_t _number_of_conflicts;
			data _gene_data;
			//schedule* _instance;
			std::vector<entities::sec_class> _sec_classes;


			double calculate_fitness();
			void make_schedule();
		public:
			explicit schedule(data gene_data);
			//schedule* get_instance();

			// accessors



			bool get_fitness_state() const;
			data get_data() const;
			size_t get_number_of_conflicts() const;
			double get_fitness();
			size_t get_sec_class_number() const;
			std::vector<entities::sec_class>& get_sec_classes();
			const std::vector<entities::sec_class>& get_sec_classes() const;

			schedule& operator=(schedule* other);

			friend std::ostream& operator<<(std::ostream& os, const schedule& other);
	};
};

#endif