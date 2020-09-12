
/*  world_margin_shape_3d.cpp                                            */

#include "world_margin_shape_3d.h"

#include "servers/physics_server_3d.h"

Vector<Vector3> WorldMarginShape3D::get_debug_mesh_lines() const {
	Plane p = get_plane();
	Vector<Vector3> points;

	Vector3 n1 = p.get_any_perpendicular_normal();
	Vector3 n2 = p.normal.cross(n1).normalized();

	Vector3 pface[4] = {
		p.normal * p.d + n1 * 10.0 + n2 * 10.0,
		p.normal * p.d + n1 * 10.0 + n2 * -10.0,
		p.normal * p.d + n1 * -10.0 + n2 * -10.0,
		p.normal * p.d + n1 * -10.0 + n2 * 10.0,
	};

	points.push_back(pface[0]);
	points.push_back(pface[1]);
	points.push_back(pface[1]);
	points.push_back(pface[2]);
	points.push_back(pface[2]);
	points.push_back(pface[3]);
	points.push_back(pface[3]);
	points.push_back(pface[0]);
	points.push_back(p.normal * p.d);
	points.push_back(p.normal * p.d + p.normal * 3);

	return points;
}

void WorldMarginShape3D::_update_shape() {
	PhysicsServer3D::get_singleton()->shape_set_data(get_shape(), plane);
	Shape3D::_update_shape();
}

void WorldMarginShape3D::set_plane(Plane p_plane) {
	plane = p_plane;
	_update_shape();
	notify_change_to_owners();
	_change_notify("plane");
}

Plane WorldMarginShape3D::get_plane() const {
	return plane;
}

void WorldMarginShape3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_plane", "plane"), &WorldMarginShape3D::set_plane);
	ClassDB::bind_method(D_METHOD("get_plane"), &WorldMarginShape3D::get_plane);

	ADD_PROPERTY(PropertyInfo(Variant::PLANE, "plane"), "set_plane", "get_plane");
}

WorldMarginShape3D::WorldMarginShape3D() :
		Shape3D(PhysicsServer3D::get_singleton()->shape_create(PhysicsServer3D::SHAPE_PLANE)) {
	set_plane(Plane(0, 1, 0, 0));
}
