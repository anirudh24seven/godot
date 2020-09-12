
/*  joints_3d_sw.h                                                       */

#ifndef JOINTS_SW_H
#define JOINTS_SW_H

#include "body_3d_sw.h"
#include "constraint_3d_sw.h"

class Joint3DSW : public Constraint3DSW {
public:
	virtual PhysicsServer3D::JointType get_type() const = 0;
	_FORCE_INLINE_ Joint3DSW(Body3DSW **p_body_ptr = nullptr, int p_body_count = 0) :
			Constraint3DSW(p_body_ptr, p_body_count) {
	}
};

#endif // JOINTS_SW_H
