
/*  ray_shape_3d.cpp                                                     */

#include "ray_shape_3d.h"

#include "servers/physics_server_3d.h"

Vector<Vector3> RayShape3D::get_debug_mesh_lines() const {
	Vector<Vector3> points;
	points.push_back(Vector3());
	points.push_back(Vector3(0, 0, get_length()));

	return points;
}

real_t RayShape3D::get_enclosing_radius() const {
	return length;
}

void RayShape3D::_update_shape() {
	Dictionary d;
	d["length"] = length;
	d["slips_on_slope"] = slips_on_slope;
	PhysicsServer3D::get_singleton()->shape_set_data(get_shape(), d);
	Shape3D::_update_shape();
}

void RayShape3D::set_length(float p_length) {
	length = p_length;
	_update_shape();
	notify_change_to_owners();
	_change_notify("length");
}

float RayShape3D::get_length() const {
	return length;
}

void RayShape3D::set_slips_on_slope(bool p_active) {
	slips_on_slope = p_active;
	_update_shape();
	notify_change_to_owners();
	_change_notify("slips_on_slope");
}

bool RayShape3D::get_slips_on_slope() const {
	return slips_on_slope;
}

void RayShape3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_length", "length"), &RayShape3D::set_length);
	ClassDB::bind_method(D_METHOD("get_length"), &RayShape3D::get_length);

	ClassDB::bind_method(D_METHOD("set_slips_on_slope", "active"), &RayShape3D::set_slips_on_slope);
	ClassDB::bind_method(D_METHOD("get_slips_on_slope"), &RayShape3D::get_slips_on_slope);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "length", PROPERTY_HINT_RANGE, "0,4096,0.01"), "set_length", "get_length");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "slips_on_slope"), "set_slips_on_slope", "get_slips_on_slope");
}

RayShape3D::RayShape3D() :
		Shape3D(PhysicsServer3D::get_singleton()->shape_create(PhysicsServer3D::SHAPE_RAY)) {
	length = 1.0;
	slips_on_slope = false;

	/* Code copied from setters to prevent the use of uninitialized variables */
	_update_shape();
	notify_change_to_owners();
	_change_notify("length");
	_change_notify("slips_on_slope");
}
