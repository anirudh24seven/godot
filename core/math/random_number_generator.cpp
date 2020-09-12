
/*  random_number_generator.cpp                                          */

#include "random_number_generator.h"

void RandomNumberGenerator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_seed", "seed"), &RandomNumberGenerator::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &RandomNumberGenerator::get_seed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");

	ClassDB::bind_method(D_METHOD("randi"), &RandomNumberGenerator::randi);
	ClassDB::bind_method(D_METHOD("randf"), &RandomNumberGenerator::randf);
	ClassDB::bind_method(D_METHOD("randfn", "mean", "deviation"), &RandomNumberGenerator::randfn, DEFVAL(0.0), DEFVAL(1.0));
	ClassDB::bind_method(D_METHOD("randf_range", "from", "to"), &RandomNumberGenerator::randf_range);
	ClassDB::bind_method(D_METHOD("randi_range", "from", "to"), &RandomNumberGenerator::randi_range);
	ClassDB::bind_method(D_METHOD("randomize"), &RandomNumberGenerator::randomize);
}
