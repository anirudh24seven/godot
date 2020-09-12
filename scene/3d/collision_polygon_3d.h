
/*  collision_polygon_3d.h                                               */

#ifndef COLLISION_POLYGON_3D_H
#define COLLISION_POLYGON_3D_H

#include "scene/3d/node_3d.h"
#include "scene/resources/shape_3d.h"

class CollisionObject3D;
class CollisionPolygon3D : public Node3D {
	GDCLASS(CollisionPolygon3D, Node3D);

protected:
	float depth;
	AABB aabb;
	Vector<Point2> polygon;

	uint32_t owner_id;
	CollisionObject3D *parent;

	bool disabled;

	void _build_polygon();

	void _update_in_shape_owner(bool p_xform_only = false);

	bool _is_editable_3d_polygon() const;

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_depth(float p_depth);
	float get_depth() const;

	void set_polygon(const Vector<Point2> &p_polygon);
	Vector<Point2> get_polygon() const;

	void set_disabled(bool p_disabled);
	bool is_disabled() const;

	virtual AABB get_item_rect() const;

	String get_configuration_warning() const override;

	CollisionPolygon3D();
};

#endif // COLLISION_POLYGON_H
