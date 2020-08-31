
/*  constraint_bullet.h                                                  */



#ifndef CONSTRAINT_BULLET_H
#define CONSTRAINT_BULLET_H

#include "bullet_utilities.h"
#include "rid_bullet.h"

#include <BulletDynamics/ConstraintSolver/btTypedConstraint.h>

/**
	@author AndreaCatania
*/

class RigidBodyBullet;
class SpaceBullet;
class btTypedConstraint;

class ConstraintBullet : public RIDBullet {
protected:
	SpaceBullet *space = nullptr;
	btTypedConstraint *constraint = nullptr;
	bool disabled_collisions_between_bodies = true;

public:
	ConstraintBullet();

	virtual void setup(btTypedConstraint *p_constraint);
	virtual void set_space(SpaceBullet *p_space);
	virtual void destroy_internal_constraint();

	void disable_collisions_between_bodies(const bool p_disabled);
	_FORCE_INLINE_ bool is_disabled_collisions_between_bodies() const { return disabled_collisions_between_bodies; }

public:
	virtual ~ConstraintBullet() {
		bulletdelete(constraint);
		constraint = nullptr;
	}

	_FORCE_INLINE_ btTypedConstraint *get_bt_constraint() { return constraint; }
};
#endif
