
/*  world_margin_shape_3d.h                                              */



#ifndef WORLD_MARGIN_SHAPE_3D_H
#define WORLD_MARGIN_SHAPE_3D_H

#include "scene/resources/shape_3d.h"

class WorldMarginShape3D : public Shape3D {
	GDCLASS(WorldMarginShape3D, Shape3D);
	Plane plane;

protected:
	static void _bind_methods();
	virtual void _update_shape() override;

public:
	void set_plane(Plane p_plane);
	Plane get_plane() const;

	virtual Vector<Vector3> get_debug_mesh_lines() const override;
	virtual real_t get_enclosing_radius() const override {
		// Should be infinite?
		return 0;
	}

	WorldMarginShape3D();
};
#endif // WORLD_MARGIN_SHAPE_H
