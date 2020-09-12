
/*  array.cpp                                                            */

#include "gdnative/array.h"

#include "core/array.h"
#include "core/os/memory.h"

#include "core/color.h"

#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

static_assert(sizeof(godot_array) == sizeof(Array), "Array size mismatch");

void GDAPI godot_array_new(godot_array *r_dest) {
	Array *dest = (Array *)r_dest;
	memnew_placement(dest, Array);
}

void GDAPI godot_array_new_copy(godot_array *r_dest, const godot_array *p_src) {
	Array *dest = (Array *)r_dest;
	const Array *src = (const Array *)p_src;
	memnew_placement(dest, Array(*src));
}

void GDAPI godot_array_new_packed_color_array(godot_array *r_dest, const godot_packed_color_array *p_pca) {
	Array *dest = (Array *)r_dest;
	Vector<Color> *pca = (Vector<Color> *)p_pca;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_new_packed_vector3_array(godot_array *r_dest, const godot_packed_vector3_array *p_pv3a) {
	Array *dest = (Array *)r_dest;
	Vector<Vector3> *pca = (Vector<Vector3> *)p_pv3a;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_new_packed_vector2_array(godot_array *r_dest, const godot_packed_vector2_array *p_pv2a) {
	Array *dest = (Array *)r_dest;
	Vector<Vector2> *pca = (Vector<Vector2> *)p_pv2a;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_new_packed_string_array(godot_array *r_dest, const godot_packed_string_array *p_psa) {
	Array *dest = (Array *)r_dest;
	Vector<String> *pca = (Vector<String> *)p_psa;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_new_packed_float32_array(godot_array *r_dest, const godot_packed_float32_array *p_pra) {
	Array *dest = (Array *)r_dest;
	Vector<float> *pca = (Vector<float> *)p_pra;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_new_packed_float64_array(godot_array *r_dest, const godot_packed_float64_array *p_pra) {
	Array *dest = (Array *)r_dest;
	Vector<double> *pca = (Vector<double> *)p_pra;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_new_packed_int32_array(godot_array *r_dest, const godot_packed_int32_array *p_pia) {
	Array *dest = (Array *)r_dest;
	Vector<int32_t> *pca = (Vector<int32_t> *)p_pia;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_new_packed_int64_array(godot_array *r_dest, const godot_packed_int64_array *p_pia) {
	Array *dest = (Array *)r_dest;
	Vector<int64_t> *pca = (Vector<int64_t> *)p_pia;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_new_packed_byte_array(godot_array *r_dest, const godot_packed_byte_array *p_pba) {
	Array *dest = (Array *)r_dest;
	Vector<uint8_t> *pca = (Vector<uint8_t> *)p_pba;
	memnew_placement(dest, Array);
	dest->resize(pca->size());

	for (int i = 0; i < dest->size(); i++) {
		Variant v = pca->operator[](i);
		dest->operator[](i) = v;
	}
}

void GDAPI godot_array_set(godot_array *p_self, const godot_int p_idx, const godot_variant *p_value) {
	Array *self = (Array *)p_self;
	Variant *val = (Variant *)p_value;
	self->operator[](p_idx) = *val;
}

godot_variant GDAPI godot_array_get(const godot_array *p_self, const godot_int p_idx) {
	godot_variant raw_dest;
	Variant *dest = (Variant *)&raw_dest;
	const Array *self = (const Array *)p_self;
	memnew_placement(dest, Variant(self->operator[](p_idx)));
	return raw_dest;
}

godot_variant GDAPI *godot_array_operator_index(godot_array *p_self, const godot_int p_idx) {
	Array *self = (Array *)p_self;
	return (godot_variant *)&self->operator[](p_idx);
}

const godot_variant GDAPI *godot_array_operator_index_const(const godot_array *p_self, const godot_int p_idx) {
	const Array *self = (const Array *)p_self;
	return (const godot_variant *)&self->operator[](p_idx);
}

void GDAPI godot_array_append(godot_array *p_self, const godot_variant *p_value) {
	Array *self = (Array *)p_self;
	Variant *val = (Variant *)p_value;
	self->append(*val);
}

void GDAPI godot_array_clear(godot_array *p_self) {
	Array *self = (Array *)p_self;
	self->clear();
}

godot_int GDAPI godot_array_count(const godot_array *p_self, const godot_variant *p_value) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	return self->count(*val);
}

godot_bool GDAPI godot_array_empty(const godot_array *p_self) {
	const Array *self = (const Array *)p_self;
	return self->empty();
}

void GDAPI godot_array_erase(godot_array *p_self, const godot_variant *p_value) {
	Array *self = (Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	self->erase(*val);
}

godot_variant GDAPI godot_array_front(const godot_array *p_self) {
	const Array *self = (const Array *)p_self;
	godot_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->front();
	return v;
}

godot_variant GDAPI godot_array_back(const godot_array *p_self) {
	const Array *self = (const Array *)p_self;
	godot_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->back();
	return v;
}

godot_int GDAPI godot_array_find(const godot_array *p_self, const godot_variant *p_what, const godot_int p_from) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_what;
	return self->find(*val, p_from);
}

godot_int GDAPI godot_array_find_last(const godot_array *p_self, const godot_variant *p_what) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_what;
	return self->find_last(*val);
}

godot_bool GDAPI godot_array_has(const godot_array *p_self, const godot_variant *p_value) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	return self->has(*val);
}

godot_int GDAPI godot_array_hash(const godot_array *p_self) {
	const Array *self = (const Array *)p_self;
	return self->hash();
}

void GDAPI godot_array_insert(godot_array *p_self, const godot_int p_pos, const godot_variant *p_value) {
	Array *self = (Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	self->insert(p_pos, *val);
}

void GDAPI godot_array_invert(godot_array *p_self) {
	Array *self = (Array *)p_self;
	self->invert();
}

godot_variant GDAPI godot_array_pop_back(godot_array *p_self) {
	Array *self = (Array *)p_self;
	godot_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->pop_back();
	return v;
}

godot_variant GDAPI godot_array_pop_front(godot_array *p_self) {
	Array *self = (Array *)p_self;
	godot_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->pop_front();
	return v;
}

void GDAPI godot_array_push_back(godot_array *p_self, const godot_variant *p_value) {
	Array *self = (Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	self->push_back(*val);
}

void GDAPI godot_array_push_front(godot_array *p_self, const godot_variant *p_value) {
	Array *self = (Array *)p_self;
	const Variant *val = (const Variant *)p_value;
	self->push_front(*val);
}

void GDAPI godot_array_remove(godot_array *p_self, const godot_int p_idx) {
	Array *self = (Array *)p_self;
	self->remove(p_idx);
}

void GDAPI godot_array_resize(godot_array *p_self, const godot_int p_size) {
	Array *self = (Array *)p_self;
	self->resize(p_size);
}

godot_int GDAPI godot_array_rfind(const godot_array *p_self, const godot_variant *p_what, const godot_int p_from) {
	const Array *self = (const Array *)p_self;
	const Variant *val = (const Variant *)p_what;
	return self->rfind(*val, p_from);
}

godot_int GDAPI godot_array_size(const godot_array *p_self) {
	const Array *self = (const Array *)p_self;
	return self->size();
}

void GDAPI godot_array_sort(godot_array *p_self) {
	Array *self = (Array *)p_self;
	self->sort();
}

void GDAPI godot_array_sort_custom(godot_array *p_self, godot_object *p_obj, const godot_string *p_func) {
	Array *self = (Array *)p_self;
	const String *func = (const String *)p_func;
	self->sort_custom((Object *)p_obj, *func);
}

godot_int GDAPI godot_array_bsearch(godot_array *p_self, const godot_variant *p_value, const godot_bool p_before) {
	Array *self = (Array *)p_self;
	return self->bsearch(*(const Variant *)p_value, p_before);
}

godot_int GDAPI godot_array_bsearch_custom(godot_array *p_self, const godot_variant *p_value, godot_object *p_obj, const godot_string *p_func, const godot_bool p_before) {
	Array *self = (Array *)p_self;
	const String *func = (const String *)p_func;
	return self->bsearch_custom(*(const Variant *)p_value, (Object *)p_obj, *func, p_before);
}

void GDAPI godot_array_destroy(godot_array *p_self) {
	((Array *)p_self)->~Array();
}

godot_array GDAPI godot_array_duplicate(const godot_array *p_self, const godot_bool p_deep) {
	const Array *self = (const Array *)p_self;
	godot_array res;
	Array *val = (Array *)&res;
	memnew_placement(val, Array);
	*val = self->duplicate(p_deep);
	return res;
}

godot_array GDAPI godot_array_slice(const godot_array *p_self, const godot_int p_begin, const godot_int p_end, const godot_int p_step, const godot_bool p_deep) {
	const Array *self = (const Array *)p_self;
	godot_array res;
	Array *val = (Array *)&res;
	memnew_placement(val, Array);
	*val = self->slice(p_begin, p_end, p_step, p_deep);
	return res;
}

godot_variant GDAPI godot_array_max(const godot_array *p_self) {
	const Array *self = (const Array *)p_self;
	godot_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->max();
	return v;
}

godot_variant GDAPI godot_array_min(const godot_array *p_self) {
	const Array *self = (const Array *)p_self;
	godot_variant v;
	Variant *val = (Variant *)&v;
	memnew_placement(val, Variant);
	*val = self->min();
	return v;
}

void GDAPI godot_array_shuffle(godot_array *p_self) {
	Array *self = (Array *)p_self;
	self->shuffle();
}

#ifdef __cplusplus
}
#endif
