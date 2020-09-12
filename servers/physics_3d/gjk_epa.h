
/*  gjk_epa.h                                                            */

#ifndef GJK_EPA_H
#define GJK_EPA_H

#include "collision_solver_3d_sw.h"
#include "shape_3d_sw.h"

bool gjk_epa_calculate_penetration(const Shape3DSW *p_shape_A, const Transform &p_transform_A, const Shape3DSW *p_shape_B, const Transform &p_transform_B, CollisionSolver3DSW::CallbackResult p_result_callback, void *p_userdata, bool p_swap = false);
bool gjk_epa_calculate_distance(const Shape3DSW *p_shape_A, const Transform &p_transform_A, const Shape3DSW *p_shape_B, const Transform &p_transform_B, Vector3 &r_result_A, Vector3 &r_result_B);

#endif
