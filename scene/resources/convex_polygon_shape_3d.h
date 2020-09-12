
/*  convex_polygon_shape_3d.h                                            */

#ifndef CONVEX_POLYGON_SHAPE_H
#define CONVEX_POLYGON_SHAPE_H

#include "scene/resources/shape_3d.h"

class ConvexPolygonShape3D : public Shape3D {
	GDCLASS(ConvexPolygonShape3D, Shape3D);
	Vector<Vector3> points;

protected:
	static void _bind_methods();

	virtual void _update_shape() override;

public:
	void set_points(const Vector<Vector3> &p_points);
	Vector<Vector3> get_points() const;

	virtual Vector<Vector3> get_debug_mesh_lines() const override;
	virtual real_t get_enclosing_radius() const override;

	ConvexPolygonShape3D();
};

#endif // CONVEX_POLYGON_SHAPE_H
