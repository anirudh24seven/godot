
/*  thread_dummy.h                                                       */

#ifndef THREAD_DUMMY_H
#define THREAD_DUMMY_H

#include "core/os/rw_lock.h"
#include "core/os/semaphore.h"
#include "core/os/thread.h"

class ThreadDummy : public Thread {
	static Thread *create(ThreadCreateCallback p_callback, void *p_user, const Settings &p_settings = Settings());

public:
	virtual ID get_id() const { return 0; };

	static void make_default();
};

class RWLockDummy : public RWLock {
	static RWLock *create();

public:
	virtual void read_lock() {}
	virtual void read_unlock() {}
	virtual Error read_try_lock() { return OK; }

	virtual void write_lock() {}
	virtual void write_unlock() {}
	virtual Error write_try_lock() { return OK; }

	static void make_default();
};

#endif // THREAD_DUMMY_H
