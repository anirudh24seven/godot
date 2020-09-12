
/*  ray_shape_3d.h                                                       */

#ifndef RAY_SHAPE_H
#define RAY_SHAPE_H
#include "scene/resources/shape_3d.h"

class RayShape3D : public Shape3D {
	GDCLASS(RayShape3D, Shape3D);
	float length;
	bool slips_on_slope;

protected:
	static void _bind_methods();
	virtual void _update_shape() override;

public:
	void set_length(float p_length);
	float get_length() const;

	void set_slips_on_slope(bool p_active);
	bool get_slips_on_slope() const;

	virtual Vector<Vector3> get_debug_mesh_lines() const override;
	virtual real_t get_enclosing_radius() const override;

	RayShape3D();
};
#endif // RAY_SHAPE_H
