
/*  thread_dummy.cpp                                                     */



#include "thread_dummy.h"

#include "core/os/memory.h"

Thread *ThreadDummy::create(ThreadCreateCallback p_callback, void *p_user, const Thread::Settings &p_settings) {
	return memnew(ThreadDummy);
}

void ThreadDummy::make_default() {
	Thread::create_func = &ThreadDummy::create;
}

RWLock *RWLockDummy::create() {
	return memnew(RWLockDummy);
}

void RWLockDummy::make_default() {
	RWLock::create_func = &RWLockDummy::create;
}
