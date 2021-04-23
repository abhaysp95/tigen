// cpp file for "extra/extra_util.hpp"

#include "../../inc/extras/extra_util.hpp"

namespace util {
	int get_random_num(size_t upto) {
		int random = rand();
		return (random - (random / upto) * upto);
	}
};
