
/*  broad_phase_octree.h                                                 */

#ifndef BROAD_PHASE_OCTREE_H
#define BROAD_PHASE_OCTREE_H

#include "broad_phase_3d_sw.h"
#include "core/math/octree.h"

class BroadPhaseOctree : public BroadPhase3DSW {
	Octree<CollisionObject3DSW, true> octree;

	static void *_pair_callback(void *, OctreeElementID, CollisionObject3DSW *, int, OctreeElementID, CollisionObject3DSW *, int);
	static void _unpair_callback(void *, OctreeElementID, CollisionObject3DSW *, int, OctreeElementID, CollisionObject3DSW *, int, void *);

	PairCallback pair_callback;
	void *pair_userdata;
	UnpairCallback unpair_callback;
	void *unpair_userdata;

public:
	// 0 is an invalid ID
	virtual ID create(CollisionObject3DSW *p_object, int p_subindex = 0);
	virtual void move(ID p_id, const AABB &p_aabb);
	virtual void set_static(ID p_id, bool p_static);
	virtual void remove(ID p_id);

	virtual CollisionObject3DSW *get_object(ID p_id) const;
	virtual bool is_static(ID p_id) const;
	virtual int get_subindex(ID p_id) const;

	virtual int cull_point(const Vector3 &p_point, CollisionObject3DSW **p_results, int p_max_results, int *p_result_indices = nullptr);
	virtual int cull_segment(const Vector3 &p_from, const Vector3 &p_to, CollisionObject3DSW **p_results, int p_max_results, int *p_result_indices = nullptr);
	virtual int cull_aabb(const AABB &p_aabb, CollisionObject3DSW **p_results, int p_max_results, int *p_result_indices = nullptr);

	virtual void set_pair_callback(PairCallback p_pair_callback, void *p_userdata);
	virtual void set_unpair_callback(UnpairCallback p_unpair_callback, void *p_userdata);

	virtual void update();

	static BroadPhase3DSW *_create();
	BroadPhaseOctree();
};

#endif // BROAD_PHASE_OCTREE_H
