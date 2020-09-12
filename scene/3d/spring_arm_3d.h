
/*  spring_arm_3d.h                                                      */

#ifndef SPRING_ARM_H
#define SPRING_ARM_H

#include "scene/3d/node_3d.h"

class SpringArm3D : public Node3D {
	GDCLASS(SpringArm3D, Node3D);

	Ref<Shape3D> shape;
	Set<RID> excluded_objects;
	float spring_length = 1;
	float current_spring_length = 0;
	bool keep_child_basis = false;
	uint32_t mask = 1;
	float margin = 0.01;

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_length(float p_length);
	float get_length() const;
	void set_shape(Ref<Shape3D> p_shape);
	Ref<Shape3D> get_shape() const;
	void set_mask(uint32_t p_mask);
	uint32_t get_mask();
	void add_excluded_object(RID p_rid);
	bool remove_excluded_object(RID p_rid);
	void clear_excluded_objects();
	float get_hit_length();
	void set_margin(float p_margin);
	float get_margin();

	SpringArm3D() {}

private:
	void process_spring();
};

#endif
