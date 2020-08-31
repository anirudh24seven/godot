
/*  pin_joint_bullet.h                                                   */



#ifndef PIN_JOINT_BULLET_H
#define PIN_JOINT_BULLET_H

#include "joint_bullet.h"

/**
	@author AndreaCatania
*/

class RigidBodyBullet;

class PinJointBullet : public JointBullet {
	class btPoint2PointConstraint *p2pConstraint;

public:
	PinJointBullet(RigidBodyBullet *p_body_a, const Vector3 &p_pos_a, RigidBodyBullet *p_body_b, const Vector3 &p_pos_b);
	~PinJointBullet();

	virtual PhysicsServer3D::JointType get_type() const { return PhysicsServer3D::JOINT_PIN; }

	void set_param(PhysicsServer3D::PinJointParam p_param, real_t p_value);
	real_t get_param(PhysicsServer3D::PinJointParam p_param) const;

	void setPivotInA(const Vector3 &p_pos);
	void setPivotInB(const Vector3 &p_pos);

	Vector3 getPivotInA();
	Vector3 getPivotInB();
};
#endif
