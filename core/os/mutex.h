
/*  mutex.h                                                              */

#ifndef MUTEX_H
#define MUTEX_H

#include "core/error_list.h"
#include "core/typedefs.h"

#if !defined(NO_THREADS)

#include <mutex>

template <class StdMutexT>
class MutexImpl {
	mutable StdMutexT mutex;

public:
	_ALWAYS_INLINE_ void lock() const {
		mutex.lock();
	}

	_ALWAYS_INLINE_ void unlock() const {
		mutex.unlock();
	}

	_ALWAYS_INLINE_ Error try_lock() const {
		return mutex.try_lock() ? OK : ERR_BUSY;
	}
};

template <class MutexT>
class MutexLock {
	const MutexT &mutex;

public:
	_ALWAYS_INLINE_ explicit MutexLock(const MutexT &p_mutex) :
			mutex(p_mutex) {
		mutex.lock();
	}

	_ALWAYS_INLINE_ ~MutexLock() {
		mutex.unlock();
	}
};

using Mutex = MutexImpl<std::recursive_mutex>; // Recursive, for general use
using BinaryMutex = MutexImpl<std::mutex>; // Non-recursive, handle with care

extern template class MutexImpl<std::recursive_mutex>;
extern template class MutexImpl<std::mutex>;
extern template class MutexLock<MutexImpl<std::recursive_mutex>>;
extern template class MutexLock<MutexImpl<std::mutex>>;

#else

class FakeMutex {
	FakeMutex() {}
};

template <class MutexT>
class MutexImpl {
public:
	_ALWAYS_INLINE_ void lock() const {}
	_ALWAYS_INLINE_ void unlock() const {}
	_ALWAYS_INLINE_ Error try_lock() const { return OK; }
};

template <class MutexT>
class MutexLock {
public:
	explicit MutexLock(const MutexT &p_mutex) {}
};

using Mutex = MutexImpl<FakeMutex>;
using BinaryMutex = MutexImpl<FakeMutex>; // Non-recursive, handle with care

#endif // !NO_THREADS

#endif // MUTEX_H
