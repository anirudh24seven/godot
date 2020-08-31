
/*  collision_solver_3d_sw.h                                             */



#ifndef COLLISION_SOLVER_SW_H
#define COLLISION_SOLVER_SW_H

#include "shape_3d_sw.h"

class CollisionSolver3DSW {
public:
	typedef void (*CallbackResult)(const Vector3 &p_point_A, const Vector3 &p_point_B, void *p_userdata);

private:
	static void concave_callback(void *p_userdata, Shape3DSW *p_convex);
	static bool solve_static_plane(const Shape3DSW *p_shape_A, const Transform &p_transform_A, const Shape3DSW *p_shape_B, const Transform &p_transform_B, CallbackResult p_result_callback, void *p_userdata, bool p_swap_result);
	static bool solve_ray(const Shape3DSW *p_shape_A, const Transform &p_transform_A, const Shape3DSW *p_shape_B, const Transform &p_transform_B, CallbackResult p_result_callback, void *p_userdata, bool p_swap_result);
	static bool solve_concave(const Shape3DSW *p_shape_A, const Transform &p_transform_A, const Shape3DSW *p_shape_B, const Transform &p_transform_B, CallbackResult p_result_callback, void *p_userdata, bool p_swap_result, real_t p_margin_A = 0, real_t p_margin_B = 0);
	static void concave_distance_callback(void *p_userdata, Shape3DSW *p_convex);
	static bool solve_distance_plane(const Shape3DSW *p_shape_A, const Transform &p_transform_A, const Shape3DSW *p_shape_B, const Transform &p_transform_B, Vector3 &r_point_A, Vector3 &r_point_B);

public:
	static bool solve_static(const Shape3DSW *p_shape_A, const Transform &p_transform_A, const Shape3DSW *p_shape_B, const Transform &p_transform_B, CallbackResult p_result_callback, void *p_userdata, Vector3 *r_sep_axis = nullptr, real_t p_margin_A = 0, real_t p_margin_B = 0);
	static bool solve_distance(const Shape3DSW *p_shape_A, const Transform &p_transform_A, const Shape3DSW *p_shape_B, const Transform &p_transform_B, Vector3 &r_point_A, Vector3 &r_point_B, const AABB &p_concave_hint, Vector3 *r_sep_axis = nullptr);
};

#endif // COLLISION_SOLVER__SW_H
