
/*  cylinder_shape_3d.cpp                                                */

#include "cylinder_shape_3d.h"
#include "servers/physics_server_3d.h"

Vector<Vector3> CylinderShape3D::get_debug_mesh_lines() const {
	float radius = get_radius();
	float height = get_height();

	Vector<Vector3> points;

	Vector3 d(0, height * 0.5, 0);
	for (int i = 0; i < 360; i++) {
		float ra = Math::deg2rad((float)i);
		float rb = Math::deg2rad((float)i + 1);
		Point2 a = Vector2(Math::sin(ra), Math::cos(ra)) * radius;
		Point2 b = Vector2(Math::sin(rb), Math::cos(rb)) * radius;

		points.push_back(Vector3(a.x, 0, a.y) + d);
		points.push_back(Vector3(b.x, 0, b.y) + d);

		points.push_back(Vector3(a.x, 0, a.y) - d);
		points.push_back(Vector3(b.x, 0, b.y) - d);

		if (i % 90 == 0) {
			points.push_back(Vector3(a.x, 0, a.y) + d);
			points.push_back(Vector3(a.x, 0, a.y) - d);
		}
	}

	return points;
}

real_t CylinderShape3D::get_enclosing_radius() const {
	return Vector2(radius, height * 0.5).length();
}

void CylinderShape3D::_update_shape() {
	Dictionary d;
	d["radius"] = radius;
	d["height"] = height;
	PhysicsServer3D::get_singleton()->shape_set_data(get_shape(), d);
	Shape3D::_update_shape();
}

void CylinderShape3D::set_radius(float p_radius) {
	radius = p_radius;
	_update_shape();
	notify_change_to_owners();
	_change_notify("radius");
}

float CylinderShape3D::get_radius() const {
	return radius;
}

void CylinderShape3D::set_height(float p_height) {
	height = p_height;
	_update_shape();
	notify_change_to_owners();
	_change_notify("height");
}

float CylinderShape3D::get_height() const {
	return height;
}

void CylinderShape3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_radius", "radius"), &CylinderShape3D::set_radius);
	ClassDB::bind_method(D_METHOD("get_radius"), &CylinderShape3D::get_radius);
	ClassDB::bind_method(D_METHOD("set_height", "height"), &CylinderShape3D::set_height);
	ClassDB::bind_method(D_METHOD("get_height"), &CylinderShape3D::get_height);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius", PROPERTY_HINT_RANGE, "0.01,4096,0.01"), "set_radius", "get_radius");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "height", PROPERTY_HINT_RANGE, "0.01,4096,0.01"), "set_height", "get_height");
}

CylinderShape3D::CylinderShape3D() :
		Shape3D(PhysicsServer3D::get_singleton()->shape_create(PhysicsServer3D::SHAPE_CYLINDER)) {
	radius = 1.0;
	height = 2.0;
	_update_shape();
}
