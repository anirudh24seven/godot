
/*  shape_3d.h                                                           */

#ifndef SHAPE_3D_H
#define SHAPE_3D_H

#include "core/resource.h"

class ArrayMesh;

class Shape3D : public Resource {
	GDCLASS(Shape3D, Resource);
	OBJ_SAVE_TYPE(Shape3D);
	RES_BASE_EXTENSION("shape");
	RID shape;
	real_t margin = 0.04;

	Ref<ArrayMesh> debug_mesh_cache;

protected:
	static void _bind_methods();

	_FORCE_INLINE_ RID get_shape() const { return shape; }
	Shape3D(RID p_shape);

	virtual void _update_shape();

public:
	virtual RID get_rid() const override { return shape; }

	Ref<ArrayMesh> get_debug_mesh();
	virtual Vector<Vector3> get_debug_mesh_lines() const = 0; // { return Vector<Vector3>(); }
	/// Returns the radius of a sphere that fully enclose this shape
	virtual real_t get_enclosing_radius() const = 0;

	void add_vertices_to_array(Vector<Vector3> &array, const Transform &p_xform);

	real_t get_margin() const;
	void set_margin(real_t p_margin);

	Shape3D();
	~Shape3D();
};

#endif // SHAPE_H
