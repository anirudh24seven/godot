
/*  step_3d_sw.h                                                         */



#ifndef STEP_SW_H
#define STEP_SW_H

#include "space_3d_sw.h"

class Step3DSW {
	uint64_t _step;

	void _populate_island(Body3DSW *p_body, Body3DSW **p_island, Constraint3DSW **p_constraint_island);
	void _setup_island(Constraint3DSW *p_island, real_t p_delta);
	void _solve_island(Constraint3DSW *p_island, int p_iterations, real_t p_delta);
	void _check_suspend(Body3DSW *p_island, real_t p_delta);

public:
	void step(Space3DSW *p_space, real_t p_delta, int p_iterations);
	Step3DSW();
};

#endif // STEP__SW_H
