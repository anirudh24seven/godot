
/*  box_shape_3d.cpp                                                     */



#include "box_shape_3d.h"
#include "servers/physics_server_3d.h"

Vector<Vector3> BoxShape3D::get_debug_mesh_lines() const {
	Vector<Vector3> lines;
	AABB aabb;
	aabb.position = -get_extents();
	aabb.size = aabb.position * -2;

	for (int i = 0; i < 12; i++) {
		Vector3 a, b;
		aabb.get_edge(i, a, b);
		lines.push_back(a);
		lines.push_back(b);
	}

	return lines;
}

real_t BoxShape3D::get_enclosing_radius() const {
	return extents.length();
}

void BoxShape3D::_update_shape() {
	PhysicsServer3D::get_singleton()->shape_set_data(get_shape(), extents);
	Shape3D::_update_shape();
}

void BoxShape3D::set_extents(const Vector3 &p_extents) {
	extents = p_extents;
	_update_shape();
	notify_change_to_owners();
	_change_notify("extents");
}

Vector3 BoxShape3D::get_extents() const {
	return extents;
}

void BoxShape3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_extents", "extents"), &BoxShape3D::set_extents);
	ClassDB::bind_method(D_METHOD("get_extents"), &BoxShape3D::get_extents);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "extents"), "set_extents", "get_extents");
}

BoxShape3D::BoxShape3D() :
		Shape3D(PhysicsServer3D::get_singleton()->shape_create(PhysicsServer3D::SHAPE_BOX)) {
	set_extents(Vector3(1, 1, 1));
}
