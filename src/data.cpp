// cpp file for "data.hpp"

#include "../inc/data.hpp"

#include "../inc/extras/extra_util.hpp"

#include <unordered_set>
#include <algorithm>

const size_t DEMO_DEPTS_SIZE = 5;
const size_t DEMO_COURSES_SIZE = 14;
const size_t DEMO_INSTRUCTORS_SIZE = 15	;
const size_t DEMO_ROOMS_SIZE = 5;
const size_t DEMO_CLASS_TIMES_SIZE = 6;

namespace gen_algo {

	data::data(): _classes_count{ 0 } {  }

	/** data::create_data() will create entities for data, but will not make any connection between entities( as for now ) */
	void data::create_data() {
		entities::room r1  ( "R1", 155 );
		entities::room r2  ( "R2", 170 );
		entities::room r3  ( "R3", 160 );
		entities::room r4  ( "R4", 180 );
		entities::room r5  ( "R5", 150 );
		entities::room r6  ( "R6", 130 );
		entities::room r7  ( "R7", 180 );
		entities::room r8  ( "R8", 164 );
		entities::room r9  ( "R9", 190 );
		entities::room r10 ( "R10", 140 );
		this->_rooms = std::vector<entities::room>{r1, r2, r3, r4, r5, r6, r7, r8, r9, r10};

		// classtimings
		entities::class_time ct1( "CT1", "MWF 09:00 - 11:00" );
		entities::class_time ct2( "CT2", "TTS 09:00 - 11:00" );
		entities::class_time ct3( "CT3", "MWF 12:00 - 14:00" );
		entities::class_time ct4( "CT4", "TTS 12:00 - 14:00" );
		entities::class_time ct5( "CT5", "MWF 15:00 - 17:00" );
		entities::class_time ct6( "CT6", "TTS 15:00 - 17:00" );
		entities::class_time ct7( "CT7", "MWF 18:00 - 20:00" );
		entities::class_time ct8( "CT8", "TTS 18:00 - 20:00" );
		this->_class_times = std::vector<entities::class_time>{ct1, ct2, ct3, ct4, ct5, ct6, ct7, ct8};

		// instructors for the batch
		entities::instructor i1 ( "I1", "Dr. Markandeya"   );
		entities::instructor i2 ( "I2", "Dr. Gautam"       );
		entities::instructor i3 ( "I3", "Dr. Bharadwaj"    );
		entities::instructor i4 ( "I4", "Dr. Shandilya"    );
		entities::instructor i5 ( "I5", "Dr. Angiras"      );
		entities::instructor i6 ( "I6", "Dr. Virajas"      );
		entities::instructor i7 ( "I7", "Dr. Kashyap"      );
		entities::instructor i8 ( "I8", "Dr. Satya"        );
		entities::instructor i9 ( "I9", "Dr. Kavya"        );
		entities::instructor i10( "I10", "Dr. Garg"        );
		entities::instructor i11( "I11", "Dr. Kapil"       );
		entities::instructor i12( "I12", "Dr. Kanad"       );
		entities::instructor i13( "I13", "Dr. Anusuya"     );
		entities::instructor i14( "I14", "Dr. Agastya"     );
		entities::instructor i15( "I15", "Dr. Vajashrava"  );
		entities::instructor i16( "I16", "Dr. Vachaspati"  );
		entities::instructor i17( "I17", "Dr. Kanada"      );
		entities::instructor i18( "I18", "Dr. Shushrut"    );
		entities::instructor i19( "I19", "Dr. Charak"      );
		entities::instructor i20( "I20", "Dr. VedVyasa"    );
		entities::instructor i21( "I21", "Dr. VarahMihira" );
		entities::instructor i22( "I22", "Dr. Sati"        );
		entities::instructor i23( "I23", "Dr. Janaki"      );
		entities::instructor i24( "I24", "Dr. Goswami"     );
		entities::instructor i25( "I25", "Dr. Parashar"    );
		entities::instructor i26( "I26", "Dr. Parashuram"  );
		entities::instructor i27( "I27", "Dr. Vaman"       );
		entities::instructor i28( "I28", "Dr. Yagyavalkya" );
		entities::instructor i29( "I29", "Dr. Nachiketa"   );
		entities::instructor i30( "I30", "Dr. Satyavan"    );
		this->_instructors = std::vector<entities::instructor>{ i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15,
				i16, i17, i18, i19, i20, i21, i22, i23, i24, i25, i26, i27, i28, i29, i30 };

		entities::course c1 ( "C1", "Automobile", 120            );
		entities::course c2 ( "C2", "Aeronautics", 150           );
		entities::course c3 ( "C3", "Metullurgy", 150            );
		entities::course c4 ( "C4", "Biological", 140            );
		entities::course c5 ( "C5", "Chemical", 150              );
		entities::course c6 ( "C6", "Embedded Programming", 120  );
		entities::course c7 ( "C7", "Web Development", 170       );
		entities::course c8 ( "C8", "Networking Security", 140   );
		entities::course c9 ( "C9", "Electronics", 130           );
		entities::course c10( "C10", "Robotics", 180             );
		entities::course c11( "C11", "GIS & Remote Sensing", 120 );
		entities::course c12( "C12", "Construction", 110         );
		entities::course c13( "C13", "Ceramic", 90               );
		entities::course c14( "C14", "UDCourse1", 130            );
		entities::course c15( "C15", "UDCourse2", 190            );
		entities::course c16( "C16", "UDCourse3", 129            );
		entities::course c17( "C17", "UDCourse4", 148            );
		entities::course c18( "C18", "UDCourse5", 160            );
		entities::course c19( "C19", "UDCourse6", 110            );
		entities::course c20( "C20", "UDCourse7", 110            );
		entities::course c21( "C21", "UDCourse8", 158            );
		this->_courses = std::vector<entities::course>{ c1, c2, c3, c4, c5, c6, c7,
			c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c21 };

		entities::department d1("Dept. of Mechanincal Engineering");
		entities::department d2("Dept. of NueroScience");
		entities::department d3("Dept. of Information Technology");
		entities::department d4("Dept. of Electrical Engineering");
		entities::department d5("Dept. of Civil Engineering");
		entities::department d6("Dept. of Undefined Name 1");
		entities::department d7("Dept. of Undefined Name 2");
		this->_depts = std::vector<entities::department>{ d1, d2, d3, d4, d5, d6, d7 };
	}

	/** this template is used to prepare data randomly for demo_data */
	template<typename push_from, typename push_to, typename t>
	void prepare_data(const push_from& obj1, push_to& obj2, const t count) {
		std::unordered_set<size_t> random_nums;
		while( random_nums.size() < count ) {
			random_nums.insert( util::rngi( obj1.size() ) );
		}
		std::for_each( begin( random_nums ), end( random_nums ), [ &obj1, &obj2 ]( const size_t x ) {
				obj2.push_back( std::move( obj1.at( x ) ) );
				} );
	}

	//void demo_data::make_connection( const data* data ) {
	demo_data::demo_data( const data* data ) {
		prepare_data( data->get_rooms(), this->_rooms, DEMO_ROOMS_SIZE );
		prepare_data( data->get_class_times(), this->_class_times, DEMO_CLASS_TIMES_SIZE );
		prepare_data( data->get_instructors(), this->_instructors, DEMO_INSTRUCTORS_SIZE );
		prepare_data( data->get_courses(), this->_courses, DEMO_COURSES_SIZE );
		prepare_data( data->get_deparatments(), this->_depts, DEMO_DEPTS_SIZE );

		// setup for course( is it possible to reduce this labour, check it again )
		this->_courses.at( 0 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[2], this->_instructors[4] });
		this->_courses.at( 1 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[4], this->_instructors[3] });
		this->_courses.at( 2 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[9] });
		this->_courses.at( 3 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[0], this->_instructors[6] });
		this->_courses.at( 4 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[3], this->_instructors[3] });
		this->_courses.at( 5 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[1] });
		this->_courses.at( 6 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[5], this->_instructors[9] });
		this->_courses.at( 7 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[1], this->_instructors[8] });
		this->_courses.at( 8 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[1], this->_instructors[11] });
		this->_courses.at( 9 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[10], this->_instructors[1], this->_instructors[13] });
		this->_courses.at( 10 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[10], this->_instructors[13] });
		this->_courses.at( 11 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[11], this->_instructors[14] });
		this->_courses.at( 12 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[12] });
		this->_courses.at( 13 ).set_instructors( std::vector<entities::instructor>{ this->_instructors[1], this->_instructors[14] });

		// setup department
		this->_depts.at( 0 ).set_courses( std::vector<entities::course>{ this->_courses[0], this->_courses[1], this->_courses[2] } );
		this->_depts.at( 1 ).set_courses( std::vector<entities::course>{ this->_courses[3], this->_courses[4] } );
		this->_depts.at( 2 ).set_courses( std::vector<entities::course>{ this->_courses[5], this->_courses[6], this->_courses[7] } );
		this->_depts.at( 3 ).set_courses( std::vector<entities::course>{ this->_courses[8], this->_courses[9], this->_courses[10] } );
		this->_depts.at( 4 ).set_courses( std::vector<entities::course>{ this->_courses[11], this->_courses[12], this->_courses[13] } );

		// set the size of total course which are going to run
		for( const auto& dept: this->_depts ) this->_classes_count += dept.get_courses().size();
	}


	selection_data::selection_data( const data* data ) {
		// just a skeleton for constructor, which will be filled with logic later
	}


	/*void data::create_data() {
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
		entities::instructor i10("I10", "Dr. Garg");
		entities::instructor i11("I11", "Dr. Kapil");
		entities::instructor i12("I12", "Dr. Kanad");
		entities::instructor i13("I13", "Dr. Anusuya");
		entities::instructor i14("I14", "Dr. Agastya");
		entities::instructor i15("I15", "Dr. Vajashrava");
		this->_instructors = std::vector<entities::instructor>{
			i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15 };

		// courses running
		entities::course c1("C1", "Automobile", 120, std::vector<entities::instructor>{i3, i5});
		entities::course c2("C2", "Aeronautics", 150, std::vector<entities::instructor>{i5, i4});
		entities::course c3("C3", "Metullurgy", 150, std::vector<entities::instructor>{i10});
		entities::course c4("C4", "Biological", 140, std::vector<entities::instructor>{i1, i7});
		entities::course c5("C5", "Chemical", 150, std::vector<entities::instructor>{i1, i7});
		entities::course c6("C6", "Embedded Programming", 120, std::vector<entities::instructor>{i2});
		entities::course c7("C7", "Web Development", 170, std::vector<entities::instructor>{i6, i9});
		entities::course c8("C8", "Networking Security", 140, std::vector<entities::instructor>{i2, i8});
		entities::course c9("C9", "Electronics", 130, std::vector<entities::instructor>{i2, i11});
		entities::course c10("C10", "Robotics", 180, std::vector<entities::instructor>{i11, i2, i14});
		entities::course c11("C11", "GIS & Remote Sensing", 120, std::vector<entities::instructor>{i11, i14});
		entities::course c12("C12", "Construction", 110, std::vector<entities::instructor>{i12, i15});
		entities::course c13("C13", "Ceramic", 90, std::vector<entities::instructor>{i13});
		entities::course c14("C14", "Mining", 100, std::vector<entities::instructor>{i12, i15});
		this->_courses = std::vector<entities::course>{c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14};

		// departments available
		entities::department d1("Dept. of Mechanincal Engineering",
				std::vector<entities::course>{c1, c2, c3});
		entities::department d2("Dept. of NueroScience", std::vector<entities::course>{c4, c5});
		entities::department d3("Dept. of Information Technology",
				std::vector<entities::course>{c6, c7, c8});
		entities::department d4("Dept. of Electrical Engineering", std::vector<entities::course>{c9, c10, c11});
		entities::department d5("Dept. of Civil Engineering", std::vector<entities::course>{c12, c13, c14});
		this->_depts = std::vector<entities::department>{d1, d2, d3, d4, d5};

		for (const entities::department& dept: this->_depts) {
			_classes_count += dept.get_courses().size();
		}
	}*/

	std::vector<entities::department> data::get_deparatments() const { return this->_depts; }

	std::vector<entities::course> data::get_courses() const { return this->_courses; }

	std::vector<entities::room> data::get_rooms() const { return this->_rooms; }

	std::vector<entities::instructor> data::get_instructors() const { return this->_instructors; }

	std::vector<entities::class_time> data::get_class_times() const { return this->_class_times; }

	size_t data::get_classes_count() const { return this->_classes_count; }
};