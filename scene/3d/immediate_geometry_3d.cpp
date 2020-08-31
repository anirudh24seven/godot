
/*  immediate_geometry_3d.cpp                                            */



#include "immediate_geometry_3d.h"

void ImmediateGeometry3D::begin(Mesh::PrimitiveType p_primitive, const Ref<Texture2D> &p_texture) {
	RS::get_singleton()->immediate_begin(im, (RS::PrimitiveType)p_primitive, p_texture.is_valid() ? p_texture->get_rid() : RID());
	if (p_texture.is_valid()) {
		cached_textures.push_back(p_texture);
	}
}

void ImmediateGeometry3D::set_normal(const Vector3 &p_normal) {
	RS::get_singleton()->immediate_normal(im, p_normal);
}

void ImmediateGeometry3D::set_tangent(const Plane &p_tangent) {
	RS::get_singleton()->immediate_tangent(im, p_tangent);
}

void ImmediateGeometry3D::set_color(const Color &p_color) {
	RS::get_singleton()->immediate_color(im, p_color);
}

void ImmediateGeometry3D::set_uv(const Vector2 &p_uv) {
	RS::get_singleton()->immediate_uv(im, p_uv);
}

void ImmediateGeometry3D::set_uv2(const Vector2 &p_uv2) {
	RS::get_singleton()->immediate_uv2(im, p_uv2);
}

void ImmediateGeometry3D::add_vertex(const Vector3 &p_vertex) {
	RS::get_singleton()->immediate_vertex(im, p_vertex);
	if (empty) {
		aabb.position = p_vertex;
		aabb.size = Vector3();
		empty = false;
	} else {
		aabb.expand_to(p_vertex);
	}
}

void ImmediateGeometry3D::end() {
	RS::get_singleton()->immediate_end(im);
}

void ImmediateGeometry3D::clear() {
	RS::get_singleton()->immediate_clear(im);
	empty = true;
	cached_textures.clear();
}

AABB ImmediateGeometry3D::get_aabb() const {
	return aabb;
}

Vector<Face3> ImmediateGeometry3D::get_faces(uint32_t p_usage_flags) const {
	return Vector<Face3>();
}

void ImmediateGeometry3D::add_sphere(int p_lats, int p_lons, float p_radius, bool p_add_uv) {
	for (int i = 1; i <= p_lats; i++) {
		double lat0 = Math_PI * (-0.5 + (double)(i - 1) / p_lats);
		double z0 = Math::sin(lat0);
		double zr0 = Math::cos(lat0);

		double lat1 = Math_PI * (-0.5 + (double)i / p_lats);
		double z1 = Math::sin(lat1);
		double zr1 = Math::cos(lat1);

		for (int j = p_lons; j >= 1; j--) {
			double lng0 = 2 * Math_PI * (double)(j - 1) / p_lons;
			double x0 = Math::cos(lng0);
			double y0 = Math::sin(lng0);

			double lng1 = 2 * Math_PI * (double)(j) / p_lons;
			double x1 = Math::cos(lng1);
			double y1 = Math::sin(lng1);

			Vector3 v[4] = {
				Vector3(x1 * zr0, z0, y1 * zr0),
				Vector3(x1 * zr1, z1, y1 * zr1),
				Vector3(x0 * zr1, z1, y0 * zr1),
				Vector3(x0 * zr0, z0, y0 * zr0)
			};

#define ADD_POINT(m_idx)                                                                                    \
	if (p_add_uv) {                                                                                         \
		set_uv(Vector2(Math::atan2(v[m_idx].x, v[m_idx].z) / Math_PI * 0.5 + 0.5, v[m_idx].y * 0.5 + 0.5)); \
		set_tangent(Plane(Vector3(-v[m_idx].z, v[m_idx].y, v[m_idx].x), 1));                                \
	}                                                                                                       \
	set_normal(v[m_idx]);                                                                                   \
	add_vertex(v[m_idx] * p_radius);

			ADD_POINT(0);
			ADD_POINT(1);
			ADD_POINT(2);

			ADD_POINT(2);
			ADD_POINT(3);
			ADD_POINT(0);
		}
	}
}

void ImmediateGeometry3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("begin", "primitive", "texture"), &ImmediateGeometry3D::begin, DEFVAL(Ref<Texture2D>()));
	ClassDB::bind_method(D_METHOD("set_normal", "normal"), &ImmediateGeometry3D::set_normal);
	ClassDB::bind_method(D_METHOD("set_tangent", "tangent"), &ImmediateGeometry3D::set_tangent);
	ClassDB::bind_method(D_METHOD("set_color", "color"), &ImmediateGeometry3D::set_color);
	ClassDB::bind_method(D_METHOD("set_uv", "uv"), &ImmediateGeometry3D::set_uv);
	ClassDB::bind_method(D_METHOD("set_uv2", "uv"), &ImmediateGeometry3D::set_uv2);
	ClassDB::bind_method(D_METHOD("add_vertex", "position"), &ImmediateGeometry3D::add_vertex);
	ClassDB::bind_method(D_METHOD("add_sphere", "lats", "lons", "radius", "add_uv"), &ImmediateGeometry3D::add_sphere, DEFVAL(true));
	ClassDB::bind_method(D_METHOD("end"), &ImmediateGeometry3D::end);
	ClassDB::bind_method(D_METHOD("clear"), &ImmediateGeometry3D::clear);
}

ImmediateGeometry3D::ImmediateGeometry3D() {
	im = RenderingServer::get_singleton()->immediate_create();
	set_base(im);
	empty = true;
}

ImmediateGeometry3D::~ImmediateGeometry3D() {
	RenderingServer::get_singleton()->free(im);
}
