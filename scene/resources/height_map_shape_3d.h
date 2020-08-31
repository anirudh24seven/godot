
/*  height_map_shape_3d.h                                                */



#ifndef HEIGHT_MAP_SHAPE_H
#define HEIGHT_MAP_SHAPE_H

#include "scene/resources/shape_3d.h"

class HeightMapShape3D : public Shape3D {
	GDCLASS(HeightMapShape3D, Shape3D);

	int map_width;
	int map_depth;
	PackedFloat32Array map_data;
	float min_height;
	float max_height;

protected:
	static void _bind_methods();
	virtual void _update_shape() override;

public:
	void set_map_width(int p_new);
	int get_map_width() const;
	void set_map_depth(int p_new);
	int get_map_depth() const;
	void set_map_data(PackedFloat32Array p_new);
	PackedFloat32Array get_map_data() const;

	virtual Vector<Vector3> get_debug_mesh_lines() const override;
	virtual real_t get_enclosing_radius() const override;

	HeightMapShape3D();
};

#endif /* !HEIGHT_MAP_SHAPE_H */
