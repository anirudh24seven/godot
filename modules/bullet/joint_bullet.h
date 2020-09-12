
/*  joint_bullet.h                                                       */

#ifndef JOINT_BULLET_H
#define JOINT_BULLET_H

#include "constraint_bullet.h"
#include "servers/physics_server_3d.h"

/**
	@author AndreaCatania
*/

class RigidBodyBullet;
class btTypedConstraint;

class JointBullet : public ConstraintBullet {
public:
	JointBullet();
	virtual ~JointBullet();

	virtual PhysicsServer3D::JointType get_type() const = 0;
};
#endif
