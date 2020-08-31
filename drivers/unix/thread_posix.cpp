
/*  thread_posix.cpp                                                     */



#include "thread_posix.h"
#include "core/script_language.h"

#if (defined(UNIX_ENABLED) || defined(PTHREAD_ENABLED)) && !defined(NO_THREADS)

#ifdef PTHREAD_BSD_SET_NAME
#include <pthread_np.h>
#endif

#include "core/os/memory.h"
#include "core/safe_refcount.h"

static void _thread_id_key_destr_callback(void *p_value) {
	memdelete(static_cast<Thread::ID *>(p_value));
}

static pthread_key_t _create_thread_id_key() {
	pthread_key_t key;
	pthread_key_create(&key, &_thread_id_key_destr_callback);
	return key;
}

pthread_key_t ThreadPosix::thread_id_key = _create_thread_id_key();
Thread::ID ThreadPosix::next_thread_id = 0;

Thread::ID ThreadPosix::get_id() const {
	return id;
}

Thread *ThreadPosix::create_thread_posix() {
	return memnew(ThreadPosix);
}

void *ThreadPosix::thread_callback(void *userdata) {
	ThreadPosix *t = reinterpret_cast<ThreadPosix *>(userdata);
	t->id = atomic_increment(&next_thread_id);
	pthread_setspecific(thread_id_key, (void *)memnew(ID(t->id)));

	ScriptServer::thread_enter(); //scripts may need to attach a stack

	t->callback(t->user);

	ScriptServer::thread_exit();

	return nullptr;
}

Thread *ThreadPosix::create_func_posix(ThreadCreateCallback p_callback, void *p_user, const Settings &) {
	ThreadPosix *tr = memnew(ThreadPosix);
	tr->callback = p_callback;
	tr->user = p_user;
	pthread_attr_init(&tr->pthread_attr);
	pthread_attr_setdetachstate(&tr->pthread_attr, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setstacksize(&tr->pthread_attr, 256 * 1024);

	pthread_create(&tr->pthread, &tr->pthread_attr, thread_callback, tr);

	return tr;
}

Thread::ID ThreadPosix::get_thread_id_func_posix() {
	void *value = pthread_getspecific(thread_id_key);

	if (value) {
		return *static_cast<ID *>(value);
	}

	ID new_id = atomic_increment(&next_thread_id);
	pthread_setspecific(thread_id_key, (void *)memnew(ID(new_id)));
	return new_id;
}

void ThreadPosix::wait_to_finish_func_posix(Thread *p_thread) {
	ThreadPosix *tp = static_cast<ThreadPosix *>(p_thread);
	ERR_FAIL_COND(!tp);
	ERR_FAIL_COND(tp->pthread == 0);

	pthread_join(tp->pthread, nullptr);
	tp->pthread = 0;
}

Error ThreadPosix::set_name_func_posix(const String &p_name) {
#ifdef PTHREAD_NO_RENAME
	return ERR_UNAVAILABLE;

#else

#ifdef PTHREAD_RENAME_SELF

	// check if thread is the same as caller
	int err = pthread_setname_np(p_name.utf8().get_data());

#else

	pthread_t running_thread = pthread_self();
#ifdef PTHREAD_BSD_SET_NAME
	pthread_set_name_np(running_thread, p_name.utf8().get_data());
	int err = 0; // Open/FreeBSD ignore errors in this function
#else
	int err = pthread_setname_np(running_thread, p_name.utf8().get_data());
#endif // PTHREAD_BSD_SET_NAME

#endif // PTHREAD_RENAME_SELF

	return err == 0 ? OK : ERR_INVALID_PARAMETER;

#endif // PTHREAD_NO_RENAME
};

void ThreadPosix::make_default() {
	create_func = create_func_posix;
	get_thread_id_func = get_thread_id_func_posix;
	wait_to_finish_func = wait_to_finish_func_posix;
	set_name_func = set_name_func_posix;
}

ThreadPosix::ThreadPosix() {
	pthread = 0;
}

ThreadPosix::~ThreadPosix() {
}

#endif
