
/*  main_loop.cpp                                                        */



#include "main_loop.h"

#include "core/script_language.h"

void MainLoop::_bind_methods() {
	ClassDB::bind_method(D_METHOD("init"), &MainLoop::init);
	ClassDB::bind_method(D_METHOD("iteration", "delta"), &MainLoop::iteration);
	ClassDB::bind_method(D_METHOD("idle", "delta"), &MainLoop::idle);
	ClassDB::bind_method(D_METHOD("finish"), &MainLoop::finish);

	BIND_VMETHOD(MethodInfo("_initialize"));
	BIND_VMETHOD(MethodInfo(Variant::BOOL, "_iteration", PropertyInfo(Variant::FLOAT, "delta")));
	BIND_VMETHOD(MethodInfo(Variant::BOOL, "_idle", PropertyInfo(Variant::FLOAT, "delta")));
	BIND_VMETHOD(MethodInfo("_finalize"));

	BIND_CONSTANT(NOTIFICATION_OS_MEMORY_WARNING);
	BIND_CONSTANT(NOTIFICATION_TRANSLATION_CHANGED);
	BIND_CONSTANT(NOTIFICATION_WM_ABOUT);
	BIND_CONSTANT(NOTIFICATION_CRASH);
	BIND_CONSTANT(NOTIFICATION_OS_IME_UPDATE);
	BIND_CONSTANT(NOTIFICATION_APPLICATION_RESUMED);
	BIND_CONSTANT(NOTIFICATION_APPLICATION_PAUSED);
	BIND_CONSTANT(NOTIFICATION_APPLICATION_FOCUS_IN);
	BIND_CONSTANT(NOTIFICATION_APPLICATION_FOCUS_OUT);

	ADD_SIGNAL(MethodInfo("on_request_permissions_result", PropertyInfo(Variant::STRING, "permission"), PropertyInfo(Variant::BOOL, "granted")));
};

void MainLoop::set_init_script(const Ref<Script> &p_init_script) {
	init_script = p_init_script;
}

void MainLoop::init() {
	if (init_script.is_valid()) {
		set_script(init_script);
	}

	if (get_script_instance()) {
		get_script_instance()->call("_initialize");
	}
}

bool MainLoop::iteration(float p_time) {
	if (get_script_instance()) {
		return get_script_instance()->call("_iteration", p_time);
	}

	return false;
}

bool MainLoop::idle(float p_time) {
	if (get_script_instance()) {
		return get_script_instance()->call("_idle", p_time);
	}

	return false;
}

void MainLoop::finish() {
	if (get_script_instance()) {
		get_script_instance()->call("_finalize");
		set_script(Variant()); //clear script
	}
}
