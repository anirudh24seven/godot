
/*  rect2.cpp                                                            */

#include "gdnative/rect2.h"

#include "core/math/transform_2d.h"
#include "core/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

static_assert(sizeof(godot_rect2) == sizeof(Rect2), "Rect2 size mismatch");
static_assert(sizeof(godot_rect2i) == sizeof(Rect2i), "Rect2i size mismatch");

// Rect2

void GDAPI godot_rect2_new_with_position_and_size(godot_rect2 *r_dest, const godot_vector2 *p_pos, const godot_vector2 *p_size) {
	const Vector2 *position = (const Vector2 *)p_pos;
	const Vector2 *size = (const Vector2 *)p_size;
	Rect2 *dest = (Rect2 *)r_dest;
	*dest = Rect2(*position, *size);
}

void GDAPI godot_rect2_new(godot_rect2 *r_dest, const godot_real p_x, const godot_real p_y, const godot_real p_width, const godot_real p_height) {
	Rect2 *dest = (Rect2 *)r_dest;
	*dest = Rect2(p_x, p_y, p_width, p_height);
}

godot_string GDAPI godot_rect2_as_string(const godot_rect2 *p_self) {
	godot_string ret;
	const Rect2 *self = (const Rect2 *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

godot_rect2i GDAPI godot_rect2_as_rect2i(const godot_rect2 *p_self) {
	godot_rect2i dest;
	const Rect2 *self = (const Rect2 *)p_self;
	*((Rect2i *)&dest) = Rect2i(*self);
	return dest;
}

godot_real GDAPI godot_rect2_get_area(const godot_rect2 *p_self) {
	const Rect2 *self = (const Rect2 *)p_self;
	return self->get_area();
}

godot_bool GDAPI godot_rect2_intersects(const godot_rect2 *p_self, const godot_rect2 *p_b) {
	const Rect2 *self = (const Rect2 *)p_self;
	const Rect2 *b = (const Rect2 *)p_b;
	return self->intersects(*b);
}

godot_bool GDAPI godot_rect2_encloses(const godot_rect2 *p_self, const godot_rect2 *p_b) {
	const Rect2 *self = (const Rect2 *)p_self;
	const Rect2 *b = (const Rect2 *)p_b;
	return self->encloses(*b);
}

godot_bool GDAPI godot_rect2_has_no_area(const godot_rect2 *p_self) {
	const Rect2 *self = (const Rect2 *)p_self;
	return self->has_no_area();
}

godot_rect2 GDAPI godot_rect2_clip(const godot_rect2 *p_self, const godot_rect2 *p_b) {
	godot_rect2 dest;
	const Rect2 *self = (const Rect2 *)p_self;
	const Rect2 *b = (const Rect2 *)p_b;
	*((Rect2 *)&dest) = self->clip(*b);
	return dest;
}

godot_rect2 GDAPI godot_rect2_merge(const godot_rect2 *p_self, const godot_rect2 *p_b) {
	godot_rect2 dest;
	const Rect2 *self = (const Rect2 *)p_self;
	const Rect2 *b = (const Rect2 *)p_b;
	*((Rect2 *)&dest) = self->merge(*b);
	return dest;
}

godot_bool GDAPI godot_rect2_has_point(const godot_rect2 *p_self, const godot_vector2 *p_point) {
	const Rect2 *self = (const Rect2 *)p_self;
	const Vector2 *point = (const Vector2 *)p_point;
	return self->has_point(*point);
}

godot_rect2 GDAPI godot_rect2_grow(const godot_rect2 *p_self, const godot_real p_by) {
	godot_rect2 dest;
	const Rect2 *self = (const Rect2 *)p_self;

	*((Rect2 *)&dest) = self->grow(p_by);
	return dest;
}

godot_rect2 GDAPI godot_rect2_grow_individual(const godot_rect2 *p_self, const godot_real p_left, const godot_real p_top, const godot_real p_right, const godot_real p_bottom) {
	godot_rect2 dest;
	const Rect2 *self = (const Rect2 *)p_self;
	*((Rect2 *)&dest) = self->grow_individual(p_left, p_top, p_right, p_bottom);
	return dest;
}

godot_rect2 GDAPI godot_rect2_grow_margin(const godot_rect2 *p_self, const godot_int p_margin, const godot_real p_by) {
	godot_rect2 dest;
	const Rect2 *self = (const Rect2 *)p_self;
	*((Rect2 *)&dest) = self->grow_margin((Margin)p_margin, p_by);
	return dest;
}

godot_rect2 GDAPI godot_rect2_abs(const godot_rect2 *p_self) {
	godot_rect2 dest;
	const Rect2 *self = (const Rect2 *)p_self;
	*((Rect2 *)&dest) = self->abs();
	return dest;
}

godot_rect2 GDAPI godot_rect2_expand(const godot_rect2 *p_self, const godot_vector2 *p_to) {
	godot_rect2 dest;
	const Rect2 *self = (const Rect2 *)p_self;
	const Vector2 *to = (const Vector2 *)p_to;
	*((Rect2 *)&dest) = self->expand(*to);
	return dest;
}

godot_bool GDAPI godot_rect2_operator_equal(const godot_rect2 *p_self, const godot_rect2 *p_b) {
	const Rect2 *self = (const Rect2 *)p_self;
	const Rect2 *b = (const Rect2 *)p_b;
	return *self == *b;
}

godot_vector2 GDAPI godot_rect2_get_position(const godot_rect2 *p_self) {
	godot_vector2 dest;
	Vector2 *d = (Vector2 *)&dest;
	const Rect2 *self = (const Rect2 *)p_self;
	*d = self->get_position();
	return dest;
}

godot_vector2 GDAPI godot_rect2_get_size(const godot_rect2 *p_self) {
	godot_vector2 dest;
	Vector2 *d = (Vector2 *)&dest;
	const Rect2 *self = (const Rect2 *)p_self;
	*d = self->get_size();
	return dest;
}

void GDAPI godot_rect2_set_position(godot_rect2 *p_self, const godot_vector2 *p_pos) {
	Rect2 *self = (Rect2 *)p_self;
	const Vector2 *position = (const Vector2 *)p_pos;
	self->set_position(*position);
}

void GDAPI godot_rect2_set_size(godot_rect2 *p_self, const godot_vector2 *p_size) {
	Rect2 *self = (Rect2 *)p_self;
	const Vector2 *size = (const Vector2 *)p_size;
	self->set_size(*size);
}

// Rect2i

void GDAPI godot_rect2i_new_with_position_and_size(godot_rect2i *r_dest, const godot_vector2i *p_pos, const godot_vector2i *p_size) {
	const Vector2i *position = (const Vector2i *)p_pos;
	const Vector2i *size = (const Vector2i *)p_size;
	Rect2i *dest = (Rect2i *)r_dest;
	*dest = Rect2i(*position, *size);
}

void GDAPI godot_rect2i_new(godot_rect2i *r_dest, const godot_int p_x, const godot_int p_y, const godot_int p_width, const godot_int p_height) {
	Rect2i *dest = (Rect2i *)r_dest;
	*dest = Rect2i(p_x, p_y, p_width, p_height);
}

godot_string GDAPI godot_rect2i_as_string(const godot_rect2i *p_self) {
	godot_string ret;
	const Rect2i *self = (const Rect2i *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

godot_rect2 GDAPI godot_rect2i_as_rect2(const godot_rect2i *p_self) {
	godot_rect2 dest;
	const Rect2i *self = (const Rect2i *)p_self;
	*((Rect2 *)&dest) = Rect2(*self);
	return dest;
}

godot_int GDAPI godot_rect2i_get_area(const godot_rect2i *p_self) {
	const Rect2i *self = (const Rect2i *)p_self;
	return self->get_area();
}

godot_bool GDAPI godot_rect2i_intersects(const godot_rect2i *p_self, const godot_rect2i *p_b) {
	const Rect2i *self = (const Rect2i *)p_self;
	const Rect2i *b = (const Rect2i *)p_b;
	return self->intersects(*b);
}

godot_bool GDAPI godot_rect2i_encloses(const godot_rect2i *p_self, const godot_rect2i *p_b) {
	const Rect2i *self = (const Rect2i *)p_self;
	const Rect2i *b = (const Rect2i *)p_b;
	return self->encloses(*b);
}

godot_bool GDAPI godot_rect2i_has_no_area(const godot_rect2i *p_self) {
	const Rect2i *self = (const Rect2i *)p_self;
	return self->has_no_area();
}

godot_rect2i GDAPI godot_rect2i_clip(const godot_rect2i *p_self, const godot_rect2i *p_b) {
	godot_rect2i dest;
	const Rect2i *self = (const Rect2i *)p_self;
	const Rect2i *b = (const Rect2i *)p_b;
	*((Rect2i *)&dest) = self->clip(*b);
	return dest;
}

godot_rect2i GDAPI godot_rect2i_merge(const godot_rect2i *p_self, const godot_rect2i *p_b) {
	godot_rect2i dest;
	const Rect2i *self = (const Rect2i *)p_self;
	const Rect2i *b = (const Rect2i *)p_b;
	*((Rect2i *)&dest) = self->merge(*b);
	return dest;
}

godot_bool GDAPI godot_rect2i_has_point(const godot_rect2i *p_self, const godot_vector2i *p_point) {
	const Rect2i *self = (const Rect2i *)p_self;
	const Vector2i *point = (const Vector2i *)p_point;
	return self->has_point(*point);
}

godot_rect2i GDAPI godot_rect2i_grow(const godot_rect2i *p_self, const godot_int p_by) {
	godot_rect2i dest;
	const Rect2i *self = (const Rect2i *)p_self;

	*((Rect2i *)&dest) = self->grow(p_by);
	return dest;
}

godot_rect2i GDAPI godot_rect2i_grow_individual(const godot_rect2i *p_self, const godot_int p_left, const godot_int p_top, const godot_int p_right, const godot_int p_bottom) {
	godot_rect2i dest;
	const Rect2i *self = (const Rect2i *)p_self;
	*((Rect2i *)&dest) = self->grow_individual(p_left, p_top, p_right, p_bottom);
	return dest;
}

godot_rect2i GDAPI godot_rect2i_grow_margin(const godot_rect2i *p_self, const godot_int p_margin, const godot_int p_by) {
	godot_rect2i dest;
	const Rect2i *self = (const Rect2i *)p_self;
	*((Rect2i *)&dest) = self->grow_margin((Margin)p_margin, p_by);
	return dest;
}

godot_rect2i GDAPI godot_rect2i_abs(const godot_rect2i *p_self) {
	godot_rect2i dest;
	const Rect2i *self = (const Rect2i *)p_self;
	*((Rect2i *)&dest) = self->abs();
	return dest;
}

godot_rect2i GDAPI godot_rect2i_expand(const godot_rect2i *p_self, const godot_vector2i *p_to) {
	godot_rect2i dest;
	const Rect2i *self = (const Rect2i *)p_self;
	const Vector2i *to = (const Vector2i *)p_to;
	*((Rect2i *)&dest) = self->expand(*to);
	return dest;
}

godot_bool GDAPI godot_rect2i_operator_equal(const godot_rect2i *p_self, const godot_rect2i *p_b) {
	const Rect2i *self = (const Rect2i *)p_self;
	const Rect2i *b = (const Rect2i *)p_b;
	return *self == *b;
}

godot_vector2i GDAPI godot_rect2i_get_position(const godot_rect2i *p_self) {
	godot_vector2i dest;
	Vector2i *d = (Vector2i *)&dest;
	const Rect2i *self = (const Rect2i *)p_self;
	*d = self->get_position();
	return dest;
}

godot_vector2i GDAPI godot_rect2i_get_size(const godot_rect2i *p_self) {
	godot_vector2i dest;
	Vector2i *d = (Vector2i *)&dest;
	const Rect2i *self = (const Rect2i *)p_self;
	*d = self->get_size();
	return dest;
}

void GDAPI godot_rect2i_set_position(godot_rect2i *p_self, const godot_vector2i *p_pos) {
	Rect2i *self = (Rect2i *)p_self;
	const Vector2i *position = (const Vector2i *)p_pos;
	self->set_position(*position);
}

void GDAPI godot_rect2i_set_size(godot_rect2i *p_self, const godot_vector2i *p_size) {
	Rect2i *self = (Rect2i *)p_self;
	const Vector2i *size = (const Vector2i *)p_size;
	self->set_size(*size);
}

#ifdef __cplusplus
}
#endif
