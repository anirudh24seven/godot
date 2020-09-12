
/*  visibility_notifier_3d.h                                             */

#ifndef VISIBILITY_NOTIFIER_H
#define VISIBILITY_NOTIFIER_H

#include "scene/3d/node_3d.h"

class Camera3D;
class VisibilityNotifier3D : public Node3D {
	GDCLASS(VisibilityNotifier3D, Node3D);

	Set<Camera3D *> cameras;

	AABB aabb;

protected:
	virtual void _screen_enter() {}
	virtual void _screen_exit() {}

	void _notification(int p_what);
	static void _bind_methods();
	friend struct SpatialIndexer;

	void _enter_camera(Camera3D *p_camera);
	void _exit_camera(Camera3D *p_camera);

public:
	void set_aabb(const AABB &p_aabb);
	AABB get_aabb() const;
	bool is_on_screen() const;

	VisibilityNotifier3D();
};

class VisibilityEnabler3D : public VisibilityNotifier3D {
	GDCLASS(VisibilityEnabler3D, VisibilityNotifier3D);

public:
	enum Enabler {
		ENABLER_PAUSE_ANIMATIONS,
		ENABLER_FREEZE_BODIES,
		ENABLER_MAX
	};

protected:
	virtual void _screen_enter() override;
	virtual void _screen_exit() override;

	bool visible;

	void _find_nodes(Node *p_node);

	Map<Node *, Variant> nodes;
	void _node_removed(Node *p_node);
	bool enabler[ENABLER_MAX];

	void _change_node_state(Node *p_node, bool p_enabled);

	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_enabler(Enabler p_enabler, bool p_enable);
	bool is_enabler_enabled(Enabler p_enabler) const;

	VisibilityEnabler3D();
};

VARIANT_ENUM_CAST(VisibilityEnabler3D::Enabler);

#endif // VISIBILITY_NOTIFIER_H
