
/*  broad_phase_3d_basic.h                                               */



#ifndef BROAD_PHASE_BASIC_H
#define BROAD_PHASE_BASIC_H

#include "broad_phase_3d_sw.h"
#include "core/map.h"

class BroadPhase3DBasic : public BroadPhase3DSW {
	struct Element {
		CollisionObject3DSW *owner;
		bool _static;
		AABB aabb;
		int subindex;
	};

	Map<ID, Element> element_map;

	ID current;

	struct PairKey {
		union {
			struct {
				ID a;
				ID b;
			};
			uint64_t key;
		};

		_FORCE_INLINE_ bool operator<(const PairKey &p_key) const {
			return key < p_key.key;
		}

		PairKey() { key = 0; }
		PairKey(ID p_a, ID p_b) {
			if (p_a > p_b) {
				a = p_b;
				b = p_a;
			} else {
				a = p_a;
				b = p_b;
			}
		}
	};

	Map<PairKey, void *> pair_map;

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
	BroadPhase3DBasic();
};

#endif // BROAD_PHASE_BASIC_H
