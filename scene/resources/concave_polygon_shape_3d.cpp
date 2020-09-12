
/*  concave_polygon_shape_3d.cpp                                         */

#include "concave_polygon_shape_3d.h"

#include "servers/physics_server_3d.h"

Vector<Vector3> ConcavePolygonShape3D::get_debug_mesh_lines() const {
	Set<DrawEdge> edges;

	Vector<Vector3> data = get_faces();
	int datalen = data.size();
	ERR_FAIL_COND_V((datalen % 3) != 0, Vector<Vector3>());

	const Vector3 *r = data.ptr();

	for (int i = 0; i < datalen; i += 3) {
		for (int j = 0; j < 3; j++) {
			DrawEdge de(r[i + j], r[i + ((j + 1) % 3)]);
			edges.insert(de);
		}
	}

	Vector<Vector3> points;
	points.resize(edges.size() * 2);
	int idx = 0;
	for (Set<DrawEdge>::Element *E = edges.front(); E; E = E->next()) {
		points.write[idx + 0] = E->get().a;
		points.write[idx + 1] = E->get().b;
		idx += 2;
	}

	return points;
}

real_t ConcavePolygonShape3D::get_enclosing_radius() const {
	Vector<Vector3> data = get_faces();
	const Vector3 *read = data.ptr();
	real_t r = 0;
	for (int i(0); i < data.size(); i++) {
		r = MAX(read[i].length_squared(), r);
	}
	return Math::sqrt(r);
}

void ConcavePolygonShape3D::_update_shape() {
	Shape3D::_update_shape();
}

void ConcavePolygonShape3D::set_faces(const Vector<Vector3> &p_faces) {
	PhysicsServer3D::get_singleton()->shape_set_data(get_shape(), p_faces);
	notify_change_to_owners();
}

Vector<Vector3> ConcavePolygonShape3D::get_faces() const {
	return PhysicsServer3D::get_singleton()->shape_get_data(get_shape());
}

void ConcavePolygonShape3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_faces", "faces"), &ConcavePolygonShape3D::set_faces);
	ClassDB::bind_method(D_METHOD("get_faces"), &ConcavePolygonShape3D::get_faces);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR3_ARRAY, "data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_INTERNAL), "set_faces", "get_faces");
}

ConcavePolygonShape3D::ConcavePolygonShape3D() :
		Shape3D(PhysicsServer3D::get_singleton()->shape_create(PhysicsServer3D::SHAPE_CONCAVE_POLYGON)) {
	//set_planes(Vector3(1,1,1));
}
