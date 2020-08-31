
/*  rid.h                                                                */



#ifndef RID_H
#define RID_H

#include "core/typedefs.h"

class RID_AllocBase;

class RID {
	friend class RID_AllocBase;
	uint64_t _id = 0;

public:
	_FORCE_INLINE_ bool operator==(const RID &p_rid) const {
		return _id == p_rid._id;
	}
	_FORCE_INLINE_ bool operator<(const RID &p_rid) const {
		return _id < p_rid._id;
	}
	_FORCE_INLINE_ bool operator<=(const RID &p_rid) const {
		return _id <= p_rid._id;
	}
	_FORCE_INLINE_ bool operator>(const RID &p_rid) const {
		return _id > p_rid._id;
	}
	_FORCE_INLINE_ bool operator!=(const RID &p_rid) const {
		return _id != p_rid._id;
	}
	_FORCE_INLINE_ bool is_valid() const { return _id != 0; }
	_FORCE_INLINE_ bool is_null() const { return _id == 0; }

	_FORCE_INLINE_ uint64_t get_id() const { return _id; }

	_FORCE_INLINE_ RID() {}
};

#endif // RID_H
