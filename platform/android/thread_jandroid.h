
/*  thread_jandroid.h                                                    */



#ifndef THREAD_POSIX_H
#define THREAD_POSIX_H

#include "core/os/thread.h"
#include <jni.h>
#include <pthread.h>
#include <sys/types.h>

class ThreadAndroid : public Thread {
	static pthread_key_t thread_id_key;
	static ID next_thread_id;

	pthread_t pthread;
	pthread_attr_t pthread_attr;
	ThreadCreateCallback callback;
	void *user;
	ID id;

	static Thread *create_thread_jandroid();

	static void *thread_callback(void *userdata);

	static Thread *create_func_jandroid(ThreadCreateCallback p_callback, void *, const Settings &);
	static ID get_thread_id_func_jandroid();
	static void wait_to_finish_func_jandroid(Thread *p_thread);

	static void _thread_destroyed(void *value);
	ThreadAndroid();

	static pthread_key_t jvm_key;
	static JavaVM *java_vm;

public:
	virtual ID get_id() const;

	static void make_default(JavaVM *p_java_vm);
	static void setup_thread();
	static JNIEnv *get_env();

	~ThreadAndroid();
};

#endif
