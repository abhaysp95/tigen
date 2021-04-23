// cpp file for "data.hpp"

#include "../inc/data.hpp"

namespace gen_algo {
	data::data(): _classes_count{} {
		//get_instance();
		this->create_data();
	}

	void data::create_data() {
		entities::room r1("R1", 155);
		entities::room r2("R2", 170);
		entities::room r3("R3", 160);
		entities::room r4("R4", 180);
		entities::room r5("R5", 150);
		this->_rooms = std::vector<entities::room>{r1, r2, r3, r4, r5};

		// classtimings
		entities::class_time ct1("CT1", "MWF 09:00 - 11:00");
		entities::class_time ct2("CT2", "MWF 12:00 - 14:00");
		entities::class_time ct3("CT3", "MWF 15:00 - 17:00");
		entities::class_time ct4("CT4", "TTS 09:00 - 11:00");
		entities::class_time ct5("CT5", "TTS 12:00 - 14:00");
		entities::class_time ct6("CT6", "MWF 15:00 - 17:00");
		this->_class_times = std::vector<entities::class_time>{ct1, ct2, ct3, ct4, ct5, ct6};

		// instructors for the batch
		entities::instructor i1("I1", "Dr. Markandeya");
		entities::instructor i2("I2", "Dr. Gautam");
		entities::instructor i3("I3", "Dr. Bharadwaj");
		entities::instructor i4("I4", "Dr. Shandilya");
		entities::instructor i5("I5", "Dr. Angiras");
		entities::instructor i6("I6", "Dr. Virajas");
		entities::instructor i7("I7", "Dr. Kashyap");
		entities::instructor i8("I8", "Dr. Satya");
		entities::instructor i9("I9", "Dr. Kavya");
		this->_instructors = std::vector<entities::instructor>{i1, i2, i3, i4, i5, i6, i7, i8, i9};

		// courses running
		entities::course c1("C1", "Automobile", 120, std::vector<entities::instructor>{i3, i5});
		entities::course c2("C2", "Aeronautics", 150, std::vector<entities::instructor>{i5, i4});
		entities::course c3("C3", "Biological", 140, std::vector<entities::instructor>{i1, i7});
		entities::course c4("C4", "Chemical", 150, std::vector<entities::instructor>{i1, i7});
		entities::course c5("C5", "Embedded Programming", 120, std::vector<entities::instructor>{i2});
		entities::course c6("C6", "Web Development", 170, std::vector<entities::instructor>{i6, i9});
		entities::course c7("C7", "Networking Security", 140, std::vector<entities::instructor>{i2, i8});
		this->_courses = std::vector<entities::course>{c1, c2, c3, c4, c5, c6, c7};

		// departments available
		entities::department d1("Dept. of Mechanincal Engineering",
				std::vector<entities::course>{c1, c2});
		entities::department d2("Dept. of NueroScience", std::vector<entities::course>{c3, c4});
		entities::department d3("Dept. of Information Technology",
				std::vector<entities::course>{c5, c6, c7});
		this->_depts = std::vector<entities::department>{d1, d2, d3};

		for (const entities::department& dept: this->_depts) {
			_classes_count += dept.get_courses().size();
		}
	}

	//data* data::get_instance() {
		/*if (!_instance) {
			this->_instance = new data;
		}*/

		// rooms available for batch
		/*entities::room r1("R1", 155);
		entities::room r2("R2", 170);
		entities::room r3("R3", 160);
		entities::room r4("R4", 180);
		entities::room r5("R5", 150);
		this->_rooms = std::vector<entities::room>{r1, r2, r3, r4, r5};*/

		// classtimings
		/*entities::class_time ct1("CT1", "MWF 09:00 - 11:00");
		entities::class_time ct2("CT2", "MWF 12:00 - 14:00");
		entities::class_time ct3("CT3", "MWF 15:00 - 17:00");
		entities::class_time ct4("CT4", "TTS 09:00 - 11:00");
		entities::class_time ct5("CT5", "TTS 12:00 - 14:00");
		entities::class_time ct6("CT6", "MWF 15:00 - 17:00");
		this->_class_times = std::vector<entities::class_time>{ct1, ct2, ct3, ct4, ct5, ct6};*/

		// instructors for the batch
		/*entities::instructor i1("I1", "Dr. Markandeya");
		entities::instructor i2("I2", "Dr. Gautam");
		entities::instructor i3("I3", "Dr. Bharadwaj");
		entities::instructor i4("I4", "Dr. Shandilya");
		entities::instructor i5("I5", "Dr. Angiras");
		entities::instructor i6("I6", "Dr. Virajas");
		entities::instructor i7("I7", "Dr. Kashyap");
		entities::instructor i8("I8", "Dr. Satya");
		entities::instructor i9("I9", "Dr. Kavya");
		this->_instructors = std::vector<entities::instructor>{i1, i2, i3, i4, i5, i6, i7, i8, i9};*/

		// courses running
		/*entities::course c1("C1", "Automobile", 120, std::vector<entities::instructor>{i3, i5});
		entities::course c2("C2", "Aeronautics", 150, std::vector<entities::instructor>{i5, i4});
		entities::course c3("C3", "Biological", 140, std::vector<entities::instructor>{i1, i7});
		entities::course c4("C4", "Chemical", 150, std::vector<entities::instructor>{i1, i7});
		entities::course c5("C5", "Embedded Programming", 120, std::vector<entities::instructor>{i2});
		entities::course c6("C6", "Web Development", 170, std::vector<entities::instructor>{i6, i9});
		entities::course c7("C7", "Networking Security", 140, std::vector<entities::instructor>{i2, i8});
		this->_courses = std::vector<entities::course>{c1, c2, c3, c4, c5, c6, c7};*/

		// departments available
		/*entities::department d1("Dept. of Mechanincal Engineering",
				std::vector<entities::course>{c1, c2});
		entities::department d2("Dept. of NueroScience", std::vector<entities::course>{c3, c4});
		entities::department d3("Dept. of Information Technology",
				std::vector<entities::course>{c5, c6, c7});
		this->_depts = std::vector<entities::department>{d1, d2, d3};

		for (const entities::department& dept: this->_depts) {
			_classes_count += dept.get_courses().size();
		}*/

		//return this->_instance;
	//}

	std::vector<entities::department> data::get_deparatments() const { return this->_depts; }
	std::vector<entities::course> data::get_courses() const { return this->_courses; }
	std::vector<entities::room> data::get_rooms() const { return this->_rooms; }
	std::vector<entities::instructor> data::get_instructors() const { return this->_instructors; }
	std::vector<entities::class_time> data::get_class_times() const { return this->_class_times; }
	size_t data::get_classes_count() const { return this->_classes_count; }
};