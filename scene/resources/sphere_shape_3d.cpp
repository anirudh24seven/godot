
/*  sphere_shape_3d.cpp                                                  */



#include "sphere_shape_3d.h"
#include "servers/physics_server_3d.h"

Vector<Vector3> SphereShape3D::get_debug_mesh_lines() const {
	float r = get_radius();

	Vector<Vector3> points;

	for (int i = 0; i <= 360; i++) {
		float ra = Math::deg2rad((float)i);
		float rb = Math::deg2rad((float)i + 1);
		Point2 a = Vector2(Math::sin(ra), Math::cos(ra)) * r;
		Point2 b = Vector2(Math::sin(rb), Math::cos(rb)) * r;

		points.push_back(Vector3(a.x, 0, a.y));
		points.push_back(Vector3(b.x, 0, b.y));
		points.push_back(Vector3(0, a.x, a.y));
		points.push_back(Vector3(0, b.x, b.y));
		points.push_back(Vector3(a.x, a.y, 0));
		points.push_back(Vector3(b.x, b.y, 0));
	}

	return points;
}

real_t SphereShape3D::get_enclosing_radius() const {
	return radius;
}

void SphereShape3D::_update_shape() {
	PhysicsServer3D::get_singleton()->shape_set_data(get_shape(), radius);
	Shape3D::_update_shape();
}

void SphereShape3D::set_radius(float p_radius) {
	radius = p_radius;
	_update_shape();
	notify_change_to_owners();
	_change_notify("radius");
}

float SphereShape3D::get_radius() const {
	return radius;
}

void SphereShape3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_radius", "radius"), &SphereShape3D::set_radius);
	ClassDB::bind_method(D_METHOD("get_radius"), &SphereShape3D::get_radius);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius", PROPERTY_HINT_RANGE, "0,4096,0.01"), "set_radius", "get_radius");
}

SphereShape3D::SphereShape3D() :
		Shape3D(PhysicsServer3D::get_singleton()->shape_create(PhysicsServer3D::SHAPE_SPHERE)) {
	set_radius(1.0);
}
