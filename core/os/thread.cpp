
/*  thread.cpp                                                           */



#include "thread.h"

Thread *(*Thread::create_func)(ThreadCreateCallback, void *, const Settings &) = nullptr;
Thread::ID (*Thread::get_thread_id_func)() = nullptr;
void (*Thread::wait_to_finish_func)(Thread *) = nullptr;
Error (*Thread::set_name_func)(const String &) = nullptr;

Thread::ID Thread::_main_thread_id = 0;

Thread::ID Thread::get_caller_id() {
	if (get_thread_id_func) {
		return get_thread_id_func();
	}
	return 0;
}

Thread *Thread::create(ThreadCreateCallback p_callback, void *p_user, const Settings &p_settings) {
	if (create_func) {
		return create_func(p_callback, p_user, p_settings);
	}
	return nullptr;
}

void Thread::wait_to_finish(Thread *p_thread) {
	if (wait_to_finish_func) {
		wait_to_finish_func(p_thread);
	}
}

Error Thread::set_name(const String &p_name) {
	if (set_name_func) {
		return set_name_func(p_name);
	}

	return ERR_UNAVAILABLE;
}
