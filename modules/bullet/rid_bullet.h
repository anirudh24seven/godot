
/*  rid_bullet.h                                                         */



#ifndef RID_BULLET_H
#define RID_BULLET_H

#include "core/rid.h"

/**
	@author AndreaCatania
*/

class BulletPhysicsServer3D;

class RIDBullet {
	RID self;
	BulletPhysicsServer3D *physicsServer;

public:
	_FORCE_INLINE_ void set_self(const RID &p_self) { self = p_self; }
	_FORCE_INLINE_ RID get_self() const { return self; }

	_FORCE_INLINE_ void _set_physics_server(BulletPhysicsServer3D *p_physicsServer) { physicsServer = p_physicsServer; }
	_FORCE_INLINE_ BulletPhysicsServer3D *get_physics_server() const { return physicsServer; }
};
#endif
