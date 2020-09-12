
/*  cone_twist_joint_bullet.h                                            */

#ifndef CONE_TWIST_JOINT_BULLET_H
#define CONE_TWIST_JOINT_BULLET_H

#include "joint_bullet.h"

/**
	@author AndreaCatania
*/

class RigidBodyBullet;

class ConeTwistJointBullet : public JointBullet {
	class btConeTwistConstraint *coneConstraint;

public:
	ConeTwistJointBullet(RigidBodyBullet *rbA, RigidBodyBullet *rbB, const Transform &rbAFrame, const Transform &rbBFrame);

	virtual PhysicsServer3D::JointType get_type() const { return PhysicsServer3D::JOINT_CONE_TWIST; }

	void set_param(PhysicsServer3D::ConeTwistJointParam p_param, real_t p_value);
	real_t get_param(PhysicsServer3D::ConeTwistJointParam p_param) const;
};
#endif
