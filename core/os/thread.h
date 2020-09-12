
/*  thread.h                                                             */

#ifndef THREAD_H
#define THREAD_H

#include "core/typedefs.h"
#include "core/ustring.h"

typedef void (*ThreadCreateCallback)(void *p_userdata);

class Thread {
public:
	enum Priority {

		PRIORITY_LOW,
		PRIORITY_NORMAL,
		PRIORITY_HIGH
	};

	struct Settings {
		Priority priority;
		Settings() { priority = PRIORITY_NORMAL; }
	};

	typedef uint64_t ID;

protected:
	static Thread *(*create_func)(ThreadCreateCallback p_callback, void *, const Settings &);
	static ID (*get_thread_id_func)();
	static void (*wait_to_finish_func)(Thread *);
	static Error (*set_name_func)(const String &);

	friend class Main;

	static ID _main_thread_id;

	Thread() {}

public:
	virtual ID get_id() const = 0;

	static Error set_name(const String &p_name);
	_FORCE_INLINE_ static ID get_main_id() { return _main_thread_id; } ///< get the ID of the main thread
	static ID get_caller_id(); ///< get the ID of the caller function ID
	static void wait_to_finish(Thread *p_thread); ///< waits until thread is finished, and deallocates it.
	static Thread *create(ThreadCreateCallback p_callback, void *p_user, const Settings &p_settings = Settings()); ///< Static function to create a thread, will call p_callback

	virtual ~Thread() {}
};

#endif // THREAD_H
