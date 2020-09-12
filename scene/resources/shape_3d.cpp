
/*  shape_3d.cpp                                                         */

#include "shape_3d.h"

#include "core/os/os.h"
#include "scene/main/scene_tree.h"
#include "scene/resources/mesh.h"
#include "servers/physics_server_3d.h"

void Shape3D::add_vertices_to_array(Vector<Vector3> &array, const Transform &p_xform) {
	Vector<Vector3> toadd = get_debug_mesh_lines();

	if (toadd.size()) {
		int base = array.size();
		array.resize(base + toadd.size());
		Vector3 *w = array.ptrw();
		for (int i = 0; i < toadd.size(); i++) {
			w[i + base] = p_xform.xform(toadd[i]);
		}
	}
}

real_t Shape3D::get_margin() const {
	return margin;
}

void Shape3D::set_margin(real_t p_margin) {
	margin = p_margin;
	PhysicsServer3D::get_singleton()->shape_set_margin(shape, margin);
}

Ref<ArrayMesh> Shape3D::get_debug_mesh() {
	if (debug_mesh_cache.is_valid()) {
		return debug_mesh_cache;
	}

	Vector<Vector3> lines = get_debug_mesh_lines();

	debug_mesh_cache = Ref<ArrayMesh>(memnew(ArrayMesh));

	if (!lines.empty()) {
		//make mesh
		Vector<Vector3> array;
		array.resize(lines.size());
		{
			Vector3 *w = array.ptrw();
			for (int i = 0; i < lines.size(); i++) {
				w[i] = lines[i];
			}
		}

		Array arr;
		arr.resize(Mesh::ARRAY_MAX);
		arr[Mesh::ARRAY_VERTEX] = array;

		SceneTree *st = Object::cast_to<SceneTree>(OS::get_singleton()->get_main_loop());

		debug_mesh_cache->add_surface_from_arrays(Mesh::PRIMITIVE_LINES, arr);

		if (st) {
			debug_mesh_cache->surface_set_material(0, st->get_debug_collision_material());
		}
	}

	return debug_mesh_cache;
}

void Shape3D::_update_shape() {
	emit_changed();
	debug_mesh_cache.unref();
}

void Shape3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_margin", "margin"), &Shape3D::set_margin);
	ClassDB::bind_method(D_METHOD("get_margin"), &Shape3D::get_margin);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "margin", PROPERTY_HINT_RANGE, "0.001,10,0.001"), "set_margin", "get_margin");
}

Shape3D::Shape3D() {
	ERR_PRINT("Default constructor must not be called!");
}

Shape3D::Shape3D(RID p_shape) :
		shape(p_shape) {}

Shape3D::~Shape3D() {
	PhysicsServer3D::get_singleton()->free(shape);
}
