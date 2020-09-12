
/*  test_ordered_hash_map.h                                              */

#ifndef TEST_ORDERED_HASH_MAP_H
#define TEST_ORDERED_HASH_MAP_H

#include "core/ordered_hash_map.h"
#include "core/os/os.h"
#include "core/pair.h"
#include "core/vector.h"

#include "tests/test_macros.h"

namespace TestOrderedHashMap {

TEST_CASE("[OrderedHashMap] Insert element") {
	OrderedHashMap<int, int> map;
	OrderedHashMap<int, int>::Element e = map.insert(42, 84);

	CHECK(e);
	CHECK(e.key() == 42);
	CHECK(e.get() == 84);
	CHECK(e.value() == 84);
	CHECK(map[42] == 84);
	CHECK(map.has(42));
	CHECK(map.find(42));
}

TEST_CASE("[OrderedHashMap] Overwrite element") {
	OrderedHashMap<int, int> map;
	map.insert(42, 84);
	map.insert(42, 1234);

	CHECK(map[42] == 1234);
}

TEST_CASE("[OrderedHashMap] Erase via element") {
	OrderedHashMap<int, int> map;
	OrderedHashMap<int, int>::Element e = map.insert(42, 84);

	map.erase(e);
	CHECK(!e);
	CHECK(!map.has(42));
	CHECK(!map.find(42));
}

TEST_CASE("[OrderedHashMap] Erase via key") {
	OrderedHashMap<int, int> map;
	map.insert(42, 84);
	map.erase(42);
	CHECK(!map.has(42));
	CHECK(!map.find(42));
}

TEST_CASE("[OrderedHashMap] Size") {
	OrderedHashMap<int, int> map;
	map.insert(42, 84);
	map.insert(123, 84);
	map.insert(123, 84);
	map.insert(0, 84);
	map.insert(123485, 84);

	CHECK(map.size() == 4);
}

TEST_CASE("[OrderedHashMap] Iteration") {
	OrderedHashMap<int, int> map;
	map.insert(42, 84);
	map.insert(123, 12385);
	map.insert(0, 12934);
	map.insert(123485, 1238888);
	map.insert(123, 111111);

	Vector<Pair<int, int>> expected;
	expected.push_back(Pair<int, int>(42, 84));
	expected.push_back(Pair<int, int>(123, 111111));
	expected.push_back(Pair<int, int>(0, 12934));
	expected.push_back(Pair<int, int>(123485, 1238888));

	int idx = 0;
	for (OrderedHashMap<int, int>::Element E = map.front(); E; E = E.next()) {
		CHECK(expected[idx] == Pair<int, int>(E.key(), E.value()));
		++idx;
	}
}

TEST_CASE("[OrderedHashMap] Const iteration") {
	OrderedHashMap<int, int> map;
	map.insert(42, 84);
	map.insert(123, 12385);
	map.insert(0, 12934);
	map.insert(123485, 1238888);
	map.insert(123, 111111);

	const OrderedHashMap<int, int> const_map = map;

	Vector<Pair<int, int>> expected;
	expected.push_back(Pair<int, int>(42, 84));
	expected.push_back(Pair<int, int>(123, 111111));
	expected.push_back(Pair<int, int>(0, 12934));
	expected.push_back(Pair<int, int>(123485, 1238888));

	int idx = 0;
	for (OrderedHashMap<int, int>::ConstElement E = const_map.front(); E; E = E.next()) {
		CHECK(expected[idx] == Pair<int, int>(E.key(), E.value()));
		++idx;
	}
}

} // namespace TestOrderedHashMap

#endif // TEST_ORDERED_HASH_MAP_H
