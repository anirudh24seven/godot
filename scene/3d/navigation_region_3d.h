
/*  navigation_region_3d.h                                               */

#ifndef NAVIGATION_REGION_H
#define NAVIGATION_REGION_H

#include "scene/3d/node_3d.h"
#include "scene/resources/mesh.h"
#include "scene/resources/navigation_mesh.h"

class Navigation3D;

class NavigationRegion3D : public Node3D {
	GDCLASS(NavigationRegion3D, Node3D);

	bool enabled = true;
	RID region;
	Ref<NavigationMesh> navmesh;

	Navigation3D *navigation = nullptr;
	Node *debug_view = nullptr;
	Thread *bake_thread = nullptr;

protected:
	void _notification(int p_what);
	static void _bind_methods();
	void _changed_callback(Object *p_changed, const char *p_prop) override;

public:
	void set_enabled(bool p_enabled);
	bool is_enabled() const;

	void set_navigation_mesh(const Ref<NavigationMesh> &p_navmesh);
	Ref<NavigationMesh> get_navigation_mesh() const;

	/// Bakes the navigation mesh in a dedicated thread; once done, automatically
	/// sets the new navigation mesh and emits a signal
	void bake_navigation_mesh();
	void _bake_finished(Ref<NavigationMesh> p_nav_mesh);

	String get_configuration_warning() const override;

	NavigationRegion3D();
	~NavigationRegion3D();
};

#endif // NAVIGATION_REGION_H
