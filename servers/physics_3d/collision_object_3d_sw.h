
/*  collision_object_3d_sw.h                                             */

#ifndef COLLISION_OBJECT_SW_H
#define COLLISION_OBJECT_SW_H

#include "broad_phase_3d_sw.h"
#include "core/self_list.h"
#include "servers/physics_server_3d.h"
#include "shape_3d_sw.h"

#ifdef DEBUG_ENABLED
#define MAX_OBJECT_DISTANCE 3.1622776601683791e+18

#define MAX_OBJECT_DISTANCE_X2 (MAX_OBJECT_DISTANCE * MAX_OBJECT_DISTANCE)
#endif

class Space3DSW;

class CollisionObject3DSW : public ShapeOwner3DSW {
public:
	enum Type {
		TYPE_AREA,
		TYPE_BODY
	};

private:
	Type type;
	RID self;
	ObjectID instance_id;
	uint32_t collision_layer;
	uint32_t collision_mask;

	struct Shape {
		Transform xform;
		Transform xform_inv;
		BroadPhase3DSW::ID bpid;
		AABB aabb_cache; //for rayqueries
		real_t area_cache;
		Shape3DSW *shape;
		bool disabled;

		Shape() { disabled = false; }
	};

	Vector<Shape> shapes;
	Space3DSW *space;
	Transform transform;
	Transform inv_transform;
	bool _static;

	SelfList<CollisionObject3DSW> pending_shape_update_list;

	void _update_shapes();

protected:
	void _update_shapes_with_motion(const Vector3 &p_motion);
	void _unregister_shapes();

	_FORCE_INLINE_ void _set_transform(const Transform &p_transform, bool p_update_shapes = true) {
#ifdef DEBUG_ENABLED

		ERR_FAIL_COND_MSG(p_transform.origin.length_squared() > MAX_OBJECT_DISTANCE_X2, "Object went too far away (more than '" + itos(MAX_OBJECT_DISTANCE) + "' units from origin).");
#endif

		transform = p_transform;
		if (p_update_shapes) {
			_update_shapes();
		}
	}
	_FORCE_INLINE_ void _set_inv_transform(const Transform &p_transform) { inv_transform = p_transform; }
	void _set_static(bool p_static);

	virtual void _shapes_changed() = 0;
	void _set_space(Space3DSW *p_space);

	bool ray_pickable;

	CollisionObject3DSW(Type p_type);

public:
	_FORCE_INLINE_ void set_self(const RID &p_self) { self = p_self; }
	_FORCE_INLINE_ RID get_self() const { return self; }

	_FORCE_INLINE_ void set_instance_id(const ObjectID &p_instance_id) { instance_id = p_instance_id; }
	_FORCE_INLINE_ ObjectID get_instance_id() const { return instance_id; }

	void _shape_changed();

	_FORCE_INLINE_ Type get_type() const { return type; }
	void add_shape(Shape3DSW *p_shape, const Transform &p_transform = Transform(), bool p_disabled = false);
	void set_shape(int p_index, Shape3DSW *p_shape);
	void set_shape_transform(int p_index, const Transform &p_transform);
	_FORCE_INLINE_ int get_shape_count() const { return shapes.size(); }
	_FORCE_INLINE_ bool is_shape_disabled(int p_index) const {
		CRASH_BAD_INDEX(p_index, shapes.size());
		return shapes[p_index].disabled;
	}
	_FORCE_INLINE_ Shape3DSW *get_shape(int p_index) const { return shapes[p_index].shape; }
	_FORCE_INLINE_ const Transform &get_shape_transform(int p_index) const { return shapes[p_index].xform; }
	_FORCE_INLINE_ const Transform &get_shape_inv_transform(int p_index) const { return shapes[p_index].xform_inv; }
	_FORCE_INLINE_ const AABB &get_shape_aabb(int p_index) const { return shapes[p_index].aabb_cache; }
	_FORCE_INLINE_ real_t get_shape_area(int p_index) const { return shapes[p_index].area_cache; }

	_FORCE_INLINE_ Transform get_transform() const { return transform; }
	_FORCE_INLINE_ Transform get_inv_transform() const { return inv_transform; }
	_FORCE_INLINE_ Space3DSW *get_space() const { return space; }

	_FORCE_INLINE_ void set_ray_pickable(bool p_enable) { ray_pickable = p_enable; }
	_FORCE_INLINE_ bool is_ray_pickable() const { return ray_pickable; }

	void set_shape_as_disabled(int p_idx, bool p_enable);
	_FORCE_INLINE_ bool is_shape_set_as_disabled(int p_idx) const {
		CRASH_BAD_INDEX(p_idx, shapes.size());
		return shapes[p_idx].disabled;
	}

	_FORCE_INLINE_ void set_collision_layer(uint32_t p_layer) {
		collision_layer = p_layer;
		_shape_changed();
	}
	_FORCE_INLINE_ uint32_t get_collision_layer() const { return collision_layer; }

	_FORCE_INLINE_ void set_collision_mask(uint32_t p_mask) {
		collision_mask = p_mask;
		_shape_changed();
	}
	_FORCE_INLINE_ uint32_t get_collision_mask() const { return collision_mask; }

	_FORCE_INLINE_ bool test_collision_mask(CollisionObject3DSW *p_other) const {
		return collision_layer & p_other->collision_mask || p_other->collision_layer & collision_mask;
	}

	void remove_shape(Shape3DSW *p_shape);
	void remove_shape(int p_index);

	virtual void set_space(Space3DSW *p_space) = 0;

	_FORCE_INLINE_ bool is_static() const { return _static; }

	virtual ~CollisionObject3DSW() {}
};

#endif // COLLISION_OBJECT_SW_H
