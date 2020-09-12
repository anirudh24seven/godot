
/*  world_3d.h                                                           */

#ifndef WORLD_3D_H
#define WORLD_3D_H

#include "core/resource.h"
#include "scene/resources/camera_effects.h"
#include "scene/resources/environment.h"
#include "servers/physics_server_3d.h"
#include "servers/rendering_server.h"

class Camera3D;
class VisibilityNotifier3D;
struct SpatialIndexer;

class World3D : public Resource {
	GDCLASS(World3D, Resource);

private:
	RID space;
	RID scenario;
	SpatialIndexer *indexer;
	Ref<Environment> environment;
	Ref<Environment> fallback_environment;
	Ref<CameraEffects> camera_effects;

protected:
	static void _bind_methods();

	friend class Camera3D;
	friend class VisibilityNotifier3D;

	void _register_camera(Camera3D *p_camera);
	void _update_camera(Camera3D *p_camera);
	void _remove_camera(Camera3D *p_camera);

	void _register_notifier(VisibilityNotifier3D *p_notifier, const AABB &p_rect);
	void _update_notifier(VisibilityNotifier3D *p_notifier, const AABB &p_rect);
	void _remove_notifier(VisibilityNotifier3D *p_notifier);
	friend class Viewport;
	void _update(uint64_t p_frame);

public:
	RID get_space() const;
	RID get_scenario() const;

	void set_environment(const Ref<Environment> &p_environment);
	Ref<Environment> get_environment() const;

	void set_fallback_environment(const Ref<Environment> &p_environment);
	Ref<Environment> get_fallback_environment() const;

	void set_camera_effects(const Ref<CameraEffects> &p_camera_effects);
	Ref<CameraEffects> get_camera_effects() const;

	void get_camera_list(List<Camera3D *> *r_cameras);

	PhysicsDirectSpaceState3D *get_direct_space_state();

	World3D();
	~World3D();
};

#endif // WORLD_3D_H
