
/*  generic_6dof_joint_bullet.h                                          */

#ifndef GENERIC_6DOF_JOINT_BULLET_H
#define GENERIC_6DOF_JOINT_BULLET_H

#include "joint_bullet.h"

/**
	@author AndreaCatania
*/

class RigidBodyBullet;

class Generic6DOFJointBullet : public JointBullet {
	class btGeneric6DofSpring2Constraint *sixDOFConstraint;

	// First is linear second is angular
	Vector3 limits_lower[2];
	Vector3 limits_upper[2];
	bool flags[3][PhysicsServer3D::G6DOF_JOINT_FLAG_MAX];

public:
	Generic6DOFJointBullet(RigidBodyBullet *rbA, RigidBodyBullet *rbB, const Transform &frameInA, const Transform &frameInB);

	virtual PhysicsServer3D::JointType get_type() const { return PhysicsServer3D::JOINT_6DOF; }

	Transform getFrameOffsetA() const;
	Transform getFrameOffsetB() const;
	Transform getFrameOffsetA();
	Transform getFrameOffsetB();

	void set_linear_lower_limit(const Vector3 &linearLower);
	void set_linear_upper_limit(const Vector3 &linearUpper);

	void set_angular_lower_limit(const Vector3 &angularLower);
	void set_angular_upper_limit(const Vector3 &angularUpper);

	void set_param(Vector3::Axis p_axis, PhysicsServer3D::G6DOFJointAxisParam p_param, real_t p_value);
	real_t get_param(Vector3::Axis p_axis, PhysicsServer3D::G6DOFJointAxisParam p_param) const;

	void set_flag(Vector3::Axis p_axis, PhysicsServer3D::G6DOFJointAxisFlag p_flag, bool p_value);
	bool get_flag(Vector3::Axis p_axis, PhysicsServer3D::G6DOFJointAxisFlag p_flag) const;

	void set_precision(int p_precision);
	int get_precision() const;
};

#endif
