
/*  vector.h                                                             */

#ifndef VECTOR_H
#define VECTOR_H

/**
 * @class Vector
 * @author Juan Linietsky
 * Vector container. Regular Vector Container. Use with care and for smaller arrays when possible. Use Vector for large arrays.
*/

#include "core/cowdata.h"
#include "core/error_macros.h"
#include "core/os/copymem.h"
#include "core/os/memory.h"
#include "core/sort_array.h"

template <class T>
class VectorWriteProxy {
public:
	_FORCE_INLINE_ T &operator[](int p_index) {
		CRASH_BAD_INDEX(p_index, ((Vector<T> *)(this))->_cowdata.size());

		return ((Vector<T> *)(this))->_cowdata.ptrw()[p_index];
	}
};

template <class T>
class Vector {
	friend class VectorWriteProxy<T>;

public:
	VectorWriteProxy<T> write;

private:
	CowData<T> _cowdata;

public:
	bool push_back(T p_elem);
	_FORCE_INLINE_ bool append(const T &p_elem) { return push_back(p_elem); } //alias

	void remove(int p_index) { _cowdata.remove(p_index); }
	void erase(const T &p_val) {
		int idx = find(p_val);
		if (idx >= 0) {
			remove(idx);
		}
	}
	void invert();

	_FORCE_INLINE_ T *ptrw() { return _cowdata.ptrw(); }
	_FORCE_INLINE_ const T *ptr() const { return _cowdata.ptr(); }
	_FORCE_INLINE_ void clear() { resize(0); }
	_FORCE_INLINE_ bool empty() const { return _cowdata.empty(); }

	_FORCE_INLINE_ T get(int p_index) { return _cowdata.get(p_index); }
	_FORCE_INLINE_ const T get(int p_index) const { return _cowdata.get(p_index); }
	_FORCE_INLINE_ void set(int p_index, const T &p_elem) { _cowdata.set(p_index, p_elem); }
	_FORCE_INLINE_ int size() const { return _cowdata.size(); }
	Error resize(int p_size) { return _cowdata.resize(p_size); }
	_FORCE_INLINE_ const T &operator[](int p_index) const { return _cowdata.get(p_index); }
	Error insert(int p_pos, T p_val) { return _cowdata.insert(p_pos, p_val); }
	int find(const T &p_val, int p_from = 0) const { return _cowdata.find(p_val, p_from); }

	void append_array(Vector<T> p_other);

	bool has(const T &p_val) {
		return find(p_val, 0) != -1;
	}

	template <class C>
	void sort_custom() {
		int len = _cowdata.size();
		if (len == 0) {
			return;
		}

		T *data = ptrw();
		SortArray<T, C> sorter;
		sorter.sort(data, len);
	}

	void sort() {
		sort_custom<_DefaultComparator<T>>();
	}

	void ordered_insert(const T &p_val) {
		int i;
		for (i = 0; i < _cowdata.size(); i++) {
			if (p_val < operator[](i)) {
				break;
			}
		}
		insert(i, p_val);
	}

	inline Vector &operator=(const Vector &p_from) {
		_cowdata._ref(p_from._cowdata);
		return *this;
	}

	Vector<uint8_t> to_byte_array() const {
		Vector<uint8_t> ret;
		ret.resize(size() * sizeof(T));
		copymem(ret.ptrw(), ptr(), sizeof(T) * size());
		return ret;
	}

	Vector<T> subarray(int p_from, int p_to) const {
		if (p_from < 0) {
			p_from = size() + p_from;
		}
		if (p_to < 0) {
			p_to = size() + p_to;
		}

		ERR_FAIL_INDEX_V(p_from, size(), Vector<T>());
		ERR_FAIL_INDEX_V(p_to, size(), Vector<T>());

		Vector<T> slice;
		int span = 1 + p_to - p_from;
		slice.resize(span);
		const T *r = ptr();
		T *w = slice.ptrw();
		for (int i = 0; i < span; ++i) {
			w[i] = r[p_from + i];
		}

		return slice;
	}

	_FORCE_INLINE_ Vector() {}
	_FORCE_INLINE_ Vector(const Vector &p_from) { _cowdata._ref(p_from._cowdata); }

	_FORCE_INLINE_ ~Vector() {}
};

template <class T>
void Vector<T>::invert() {
	for (int i = 0; i < size() / 2; i++) {
		T *p = ptrw();
		SWAP(p[i], p[size() - i - 1]);
	}
}

template <class T>
void Vector<T>::append_array(Vector<T> p_other) {
	const int ds = p_other.size();
	if (ds == 0) {
		return;
	}
	const int bs = size();
	resize(bs + ds);
	for (int i = 0; i < ds; ++i) {
		ptrw()[bs + i] = p_other[i];
	}
}

template <class T>
bool Vector<T>::push_back(T p_elem) {
	Error err = resize(size() + 1);
	ERR_FAIL_COND_V(err, true);
	set(size() - 1, p_elem);

	return false;
}

#endif // VECTOR_H
