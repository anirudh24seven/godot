
/*  convex_polygon_shape_3d.cpp                                          */



#include "convex_polygon_shape_3d.h"
#include "core/math/quick_hull.h"
#include "servers/physics_server_3d.h"

Vector<Vector3> ConvexPolygonShape3D::get_debug_mesh_lines() const {
	Vector<Vector3> points = get_points();

	if (points.size() > 3) {
		Vector<Vector3> varr = Variant(points);
		Geometry3D::MeshData md;
		Error err = QuickHull::build(varr, md);
		if (err == OK) {
			Vector<Vector3> lines;
			lines.resize(md.edges.size() * 2);
			for (int i = 0; i < md.edges.size(); i++) {
				lines.write[i * 2 + 0] = md.vertices[md.edges[i].a];
				lines.write[i * 2 + 1] = md.vertices[md.edges[i].b];
			}
			return lines;
		}
	}

	return Vector<Vector3>();
}

real_t ConvexPolygonShape3D::get_enclosing_radius() const {
	Vector<Vector3> data = get_points();
	const Vector3 *read = data.ptr();
	real_t r = 0;
	for (int i(0); i < data.size(); i++) {
		r = MAX(read[i].length_squared(), r);
	}
	return Math::sqrt(r);
}

void ConvexPolygonShape3D::_update_shape() {
	PhysicsServer3D::get_singleton()->shape_set_data(get_shape(), points);
	Shape3D::_update_shape();
}

void ConvexPolygonShape3D::set_points(const Vector<Vector3> &p_points) {
	points = p_points;
	_update_shape();
	notify_change_to_owners();
}

Vector<Vector3> ConvexPolygonShape3D::get_points() const {
	return points;
}

void ConvexPolygonShape3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_points", "points"), &ConvexPolygonShape3D::set_points);
	ClassDB::bind_method(D_METHOD("get_points"), &ConvexPolygonShape3D::get_points);

	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "points"), "set_points", "get_points");
}

ConvexPolygonShape3D::ConvexPolygonShape3D() :
		Shape3D(PhysicsServer3D::get_singleton()->shape_create(PhysicsServer3D::SHAPE_CONVEX_POLYGON)) {
}
