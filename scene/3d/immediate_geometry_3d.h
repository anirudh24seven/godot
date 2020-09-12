
/*  immediate_geometry_3d.h                                              */

#ifndef IMMEDIATE_GEOMETRY_3D_H
#define IMMEDIATE_GEOMETRY_3D_H

#include "scene/3d/visual_instance_3d.h"
#include "scene/resources/mesh.h"

class ImmediateGeometry3D : public GeometryInstance3D {
	GDCLASS(ImmediateGeometry3D, GeometryInstance3D);

	RID im;
	//a list of textures drawn need to be kept, to avoid references
	// in RenderingServer from becoming invalid if the texture is no longer used
	List<Ref<Texture2D>> cached_textures;
	bool empty;
	AABB aabb;

protected:
	static void _bind_methods();

public:
	void begin(Mesh::PrimitiveType p_primitive, const Ref<Texture2D> &p_texture = Ref<Texture2D>());
	void set_normal(const Vector3 &p_normal);
	void set_tangent(const Plane &p_tangent);
	void set_color(const Color &p_color);
	void set_uv(const Vector2 &p_uv);
	void set_uv2(const Vector2 &p_uv2);

	void add_vertex(const Vector3 &p_vertex);

	void end();
	void clear();

	void add_sphere(int p_lats, int p_lons, float p_radius, bool p_add_uv = true);

	virtual AABB get_aabb() const override;
	virtual Vector<Face3> get_faces(uint32_t p_usage_flags) const override;

	ImmediateGeometry3D();
	~ImmediateGeometry3D();
};

#endif // IMMEDIATE_GEOMETRY_H
