
/*  world_2d.h                                                           */



#ifndef WORLD_2D_H
#define WORLD_2D_H

#include "core/project_settings.h"
#include "core/resource.h"
#include "servers/physics_server_2d.h"

class VisibilityNotifier2D;
class Viewport;
struct SpatialIndexer2D;

class World2D : public Resource {
	GDCLASS(World2D, Resource);

	RID canvas;
	RID space;

	SpatialIndexer2D *indexer;

protected:
	static void _bind_methods();
	friend class Viewport;
	friend class VisibilityNotifier2D;

	void _register_viewport(Viewport *p_viewport, const Rect2 &p_rect);
	void _update_viewport(Viewport *p_viewport, const Rect2 &p_rect);
	void _remove_viewport(Viewport *p_viewport);

	void _register_notifier(VisibilityNotifier2D *p_notifier, const Rect2 &p_rect);
	void _update_notifier(VisibilityNotifier2D *p_notifier, const Rect2 &p_rect);
	void _remove_notifier(VisibilityNotifier2D *p_notifier);

	void _update();

public:
	RID get_canvas();
	RID get_space();

	PhysicsDirectSpaceState2D *get_direct_space_state();

	void get_viewport_list(List<Viewport *> *r_viewports);

	World2D();
	~World2D();
};

#endif // WORLD_2D_H
