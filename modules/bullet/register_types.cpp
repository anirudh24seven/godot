
/*  register_types.cpp                                                   */



#include "register_types.h"

#include "bullet_physics_server.h"
#include "core/class_db.h"
#include "core/project_settings.h"

/**
	@author AndreaCatania
*/

#ifndef _3D_DISABLED
PhysicsServer3D *_createBulletPhysicsCallback() {
	return memnew(BulletPhysicsServer3D);
}
#endif

void register_bullet_types() {
#ifndef _3D_DISABLED
	PhysicsServer3DManager::register_server("Bullet", &_createBulletPhysicsCallback);
	PhysicsServer3DManager::set_default_server("Bullet", 1);

	GLOBAL_DEF("physics/3d/active_soft_world", true);
	ProjectSettings::get_singleton()->set_custom_property_info("physics/3d/active_soft_world", PropertyInfo(Variant::BOOL, "physics/3d/active_soft_world"));
#endif
}

void unregister_bullet_types() {
}
