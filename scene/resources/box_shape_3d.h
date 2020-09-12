
/*  box_shape_3d.h                                                       */

#ifndef BOX_SHAPE_H
#define BOX_SHAPE_H

#include "scene/resources/shape_3d.h"

class BoxShape3D : public Shape3D {
	GDCLASS(BoxShape3D, Shape3D);
	Vector3 extents;

protected:
	static void _bind_methods();

	virtual void _update_shape() override;

public:
	void set_extents(const Vector3 &p_extents);
	Vector3 get_extents() const;

	virtual Vector<Vector3> get_debug_mesh_lines() const override;
	virtual real_t get_enclosing_radius() const override;

	BoxShape3D();
};

#endif // BOX_SHAPE_H
