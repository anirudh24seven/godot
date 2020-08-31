
/*  broad_phase_3d_sw.h                                                  */



#ifndef BROAD_PHASE_SW_H
#define BROAD_PHASE_SW_H

#include "core/math/aabb.h"
#include "core/math/math_funcs.h"

class CollisionObject3DSW;

class BroadPhase3DSW {
public:
	typedef BroadPhase3DSW *(*CreateFunction)();

	static CreateFunction create_func;

	typedef uint32_t ID;

	typedef void *(*PairCallback)(CollisionObject3DSW *A, int p_subindex_A, CollisionObject3DSW *B, int p_subindex_B, void *p_userdata);
	typedef void (*UnpairCallback)(CollisionObject3DSW *A, int p_subindex_A, CollisionObject3DSW *B, int p_subindex_B, void *p_data, void *p_userdata);

	// 0 is an invalid ID
	virtual ID create(CollisionObject3DSW *p_object_, int p_subindex = 0) = 0;
	virtual void move(ID p_id, const AABB &p_aabb) = 0;
	virtual void set_static(ID p_id, bool p_static) = 0;
	virtual void remove(ID p_id) = 0;

	virtual CollisionObject3DSW *get_object(ID p_id) const = 0;
	virtual bool is_static(ID p_id) const = 0;
	virtual int get_subindex(ID p_id) const = 0;

	virtual int cull_point(const Vector3 &p_point, CollisionObject3DSW **p_results, int p_max_results, int *p_result_indices = nullptr) = 0;
	virtual int cull_segment(const Vector3 &p_from, const Vector3 &p_to, CollisionObject3DSW **p_results, int p_max_results, int *p_result_indices = nullptr) = 0;
	virtual int cull_aabb(const AABB &p_aabb, CollisionObject3DSW **p_results, int p_max_results, int *p_result_indices = nullptr) = 0;

	virtual void set_pair_callback(PairCallback p_pair_callback, void *p_userdata) = 0;
	virtual void set_unpair_callback(UnpairCallback p_unpair_callback, void *p_userdata) = 0;

	virtual void update() = 0;

	virtual ~BroadPhase3DSW();
};

#endif // BROAD_PHASE__SW_H
