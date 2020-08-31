
/*  cylinder_shape_3d.h                                                  */



#ifndef CYLINDER_SHAPE_3D_H
#define CYLINDER_SHAPE_3D_H

#include "scene/resources/shape_3d.h"

class CylinderShape3D : public Shape3D {
	GDCLASS(CylinderShape3D, Shape3D);
	float radius;
	float height;

protected:
	static void _bind_methods();
	virtual void _update_shape() override;

public:
	void set_radius(float p_radius);
	float get_radius() const;
	void set_height(float p_height);
	float get_height() const;

	virtual Vector<Vector3> get_debug_mesh_lines() const override;
	virtual real_t get_enclosing_radius() const override;

	CylinderShape3D();
};

#endif // CYLINDER_SHAPE_H
