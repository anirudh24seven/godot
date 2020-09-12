
/*  area_pair_3d_sw.h                                                    */

#ifndef AREA_PAIR_SW_H
#define AREA_PAIR_SW_H

#include "area_3d_sw.h"
#include "body_3d_sw.h"
#include "constraint_3d_sw.h"

class AreaPair3DSW : public Constraint3DSW {
	Body3DSW *body;
	Area3DSW *area;
	int body_shape;
	int area_shape;
	bool colliding;

public:
	bool setup(real_t p_step);
	void solve(real_t p_step);

	AreaPair3DSW(Body3DSW *p_body, int p_body_shape, Area3DSW *p_area, int p_area_shape);
	~AreaPair3DSW();
};

class Area2Pair3DSW : public Constraint3DSW {
	Area3DSW *area_a;
	Area3DSW *area_b;
	int shape_a;
	int shape_b;
	bool colliding;

public:
	bool setup(real_t p_step);
	void solve(real_t p_step);

	Area2Pair3DSW(Area3DSW *p_area_a, int p_shape_a, Area3DSW *p_area_b, int p_shape_b);
	~Area2Pair3DSW();
};

#endif // AREA_PAIR__SW_H
