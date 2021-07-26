// cpp file for "schedule.hpp"

//#include "../inc/schedule.hpp"
//#include "../inc/extras/extra_util.hpp"

#include <glib/schedule.hpp>
#include <extras/extra_util.hpp>

#include <algorithm>
#include <string>
#include <sstream>

namespace gen_algo {
	schedule::schedule(data gene_data): _is_fitness_changed{true}, _fitness(-1),
		_sec_class_number{}, _number_of_conflicts{}, _gene_data{gene_data} {
		this->_sec_classes.reserve(this->_gene_data.get_classes_count());
		this->make_schedule();
	}
	// is initialization of _gene_data is correct ?

	void schedule::make_schedule() {
		std::vector<entities::department> data_depts{this->_gene_data.get_departments()};
		for (entities::department& dept: data_depts) {
			for (entities::course& crs: dept.get_courses()) {
				entities::sec_class new_class(this->_sec_class_number++, dept, crs);

				new_class.set_room( this->_gene_data.get_rooms()[
						util::rngi( this->_gene_data.get_rooms().size() )
				] );
				new_class.set_instructor( this->_gene_data.get_instructors()[
						util::rngi( this->_gene_data.get_instructors().size() )
				] );
				new_class.set_class_time( this->_gene_data.get_class_times()[
						util::rngi( this->_gene_data.get_class_times().size()  )
				] );

				this->_sec_classes.push_back(new_class);
			}
		}
	}

	/*schedule* schedule::get_instance() {
		std::vector<entities::department> data_depts{this->_gene_data->get_departments()};
		for (entities::department& dept: data_depts) {
			for (entities::course& crs: dept.get_courses()) {
				entities::sec_class new_class(this->_sec_class_number++, dept, crs);
				new_class.set_room(this->_gene_data->get_rooms().at(
							util::get_random_num(this->_gene_data->get_rooms().size())
							));
				new_class.set_instructor(this->_gene_data->get_instructors().at(
							util::get_random_num(this->_gene_data->get_instructors().size())
							));
				new_class.set_class_time(this->_gene_data->get_class_times().at(
							util::get_random_num(this->_gene_data->get_class_times().size())
							));
				this->_sec_classes.push_back(new_class);
			}
		}
		return this;
	}*/

	bool schedule::get_fitness_state() const { return this->_is_fitness_changed; }

	data schedule::get_data() const { return this->_gene_data; }

	size_t schedule::get_number_of_conflicts() const { return this->_number_of_conflicts; }

	size_t schedule::get_sec_class_number() const { return this->_sec_class_number; }

	std::vector<entities::sec_class>& schedule::get_sec_classes() {
		this->_is_fitness_changed = true;
		return this->_sec_classes;
	}

	const std::vector<entities::sec_class>& schedule::get_sec_classes() const { return this->_sec_classes; }

	double schedule::get_fitness() {
		if (this->_is_fitness_changed) {
			this->_fitness = calculate_fitness();
			this->_is_fitness_changed = false;
		}
		return this->_fitness;
	}

	template <typename T, typename Pred>
	std::vector<T> filter(const std::vector<T>& vec, Pred p) {
		std::vector<T> res;
		std::copy_if(vec.begin(), vec.end(), std::back_inserter(res), p);
		return res;
	}

	double schedule::calculate_fitness() {
		this->_number_of_conflicts = 0;
		for (const entities::sec_class& cls: this->_sec_classes) {
			if (cls.get_room().get_capacity() < cls.get_course().get_max_students())
				this->_number_of_conflicts++;
			std::vector<entities::sec_class>&& up_cls = filter(this->_sec_classes,
					[&](const entities::sec_class& tcls) {
					return (&tcls - &(*this->_sec_classes.cbegin())) >= (&cls - &(*this->_sec_classes.cbegin()));
					});
			for (const entities::sec_class& ucls: up_cls) {
				if ((cls.get_class_time() == ucls.get_class_time())
						&& (cls.get_id() != ucls.get_id())) {
					if (cls.get_room() == ucls.get_room())
						this->_number_of_conflicts++;
					if (cls.get_instructor() == ucls.get_instructor())
						this->_number_of_conflicts++;
				}
			}
		}
		//return this->_number_of_conflicts;
		return 1 / static_cast<double>(this->_number_of_conflicts + 1);
	}



	/**
	  this function does the same work as above and is easier to read
	  honestly, I don't see any cons in not using this one, so if you didn't
	  understood the above function(and the template it is using) just read
	  this
	*/
	/* double schedule::calculate_fitness() {
		this->_number_of_conflicts = 0;
		for (std::vector<entities::sec_class>::const_iterator citer = this->_sec_classes.cbegin();
				citer != this->_sec_classes.cend(); ++citer) {
			if (citer->get_room().get_capacity() < citer->get_course().get_max_students())
				this->_number_of_conflicts++;
			std::vector<entities::sec_class>&& up_cls = std::vector<entities::sec_class>{
				citer, this->_sec_classes.cend()
			};
			for (const entities::sec_class& ucls: up_cls) {
				if ((citer->get_class_time() == ucls.get_class_time())
						&& (citer->get_id() != ucls.get_id())) {
					if (citer->get_room() == ucls.get_room())
						this->_number_of_conflicts++;
					if (citer->get_instructor() == ucls.get_instructor())
						this->_number_of_conflicts++;
				}
			}
		}
		return 1 / static_cast<double>(this->_number_of_conflicts + 1);
	} */


	schedule& schedule::operator=(schedule* other) {
		this->_is_fitness_changed = other->get_fitness_state();
		this->_fitness = other->get_fitness();
		this->_sec_class_number = other->get_sec_class_number();
		this->_number_of_conflicts = other->get_number_of_conflicts();
		this->_sec_classes = other->get_sec_classes();
		return *this;
	}


	/*std::ostream& schedule::dump(std::ostream& os) const {
		std::string return_res;
		for (std::vector<entities::sec_class>::const_iterator citer = this->_sec_classes.cbegin();
				citer != this->_sec_classes.cend(); ++citer) {
			std::ostringstream ss;
			ss << citer->dump(os).rdbuf();
			return_res += ss.str();
			if (citer < this->_sec_classes.cend() - 1)
				return_res += ", ";
			//os << citer->dump(os);
		}
		return os << return_res;
	}*/
	// not to sure about above dump method(have to check whether it's
	// correct(it compiles successfully, but that doesn't says everything))

	// alternative to dump(above function)
	std::ostream& operator<<(std::ostream& os, const schedule& other) {
		for (std::vector<entities::sec_class>::const_iterator citer = other.get_sec_classes().cbegin();
				citer != other.get_sec_classes().cend(); ++citer) {
			os << *citer;
			if (citer < other.get_sec_classes().cend() - 1)
				os << ", ";
		}
		return os;
	}

};