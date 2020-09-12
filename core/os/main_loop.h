
/*  main_loop.h                                                          */

#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include "core/input/input_event.h"
#include "core/reference.h"
#include "core/script_language.h"

class MainLoop : public Object {
	GDCLASS(MainLoop, Object);
	OBJ_CATEGORY("Main Loop");

	Ref<Script> init_script;

protected:
	static void _bind_methods();

public:
	enum {
		//make sure these are replicated in Node
		NOTIFICATION_OS_MEMORY_WARNING = 2009,
		NOTIFICATION_TRANSLATION_CHANGED = 2010,
		NOTIFICATION_WM_ABOUT = 2011,
		NOTIFICATION_CRASH = 2012,
		NOTIFICATION_OS_IME_UPDATE = 2013,
		NOTIFICATION_APPLICATION_RESUMED = 2014,
		NOTIFICATION_APPLICATION_PAUSED = 2015,
		NOTIFICATION_APPLICATION_FOCUS_IN = 2016,
		NOTIFICATION_APPLICATION_FOCUS_OUT = 2017,
	};

	virtual void init();
	virtual bool iteration(float p_time);
	virtual bool idle(float p_time);
	virtual void finish();

	void set_init_script(const Ref<Script> &p_init_script);

	MainLoop() {}
	virtual ~MainLoop() {}
};

#endif // MAIN_LOOP_H
