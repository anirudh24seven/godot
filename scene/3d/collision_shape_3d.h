
/*  collision_shape_3d.h                                                 */



#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include "scene/3d/node_3d.h"
#include "scene/resources/shape_3d.h"
class CollisionObject3D;
class CollisionShape3D : public Node3D {
	GDCLASS(CollisionShape3D, Node3D);
	OBJ_CATEGORY("3D Physics Nodes");

	Ref<Shape3D> shape;

	uint32_t owner_id;
	CollisionObject3D *parent;

	Node *debug_shape;
	bool debug_shape_dirty;

	void resource_changed(RES res);
	bool disabled;

protected:
	void _update_debug_shape();
	void _shape_changed();

	void _update_in_shape_owner(bool p_xform_only = false);

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void make_convex_from_brothers();

	void set_shape(const Ref<Shape3D> &p_shape);
	Ref<Shape3D> get_shape() const;

	void set_disabled(bool p_disabled);
	bool is_disabled() const;

	String get_configuration_warning() const override;

	CollisionShape3D();
	~CollisionShape3D();
};

#endif // BODY_VOLUME_H
