
/*  editor_debugger_plugin.cpp                                           */

#include "editor_debugger_plugin.h"

#include "editor/debugger/script_editor_debugger.h"

void EditorDebuggerPlugin::_breaked(bool p_really_did, bool p_can_debug) {
	if (p_really_did) {
		emit_signal("breaked", p_can_debug);
	} else {
		emit_signal("continued");
	}
}

void EditorDebuggerPlugin::_started() {
	emit_signal("started");
}

void EditorDebuggerPlugin::_stopped() {
	emit_signal("stopped");
}

void EditorDebuggerPlugin::_bind_methods() {
	ClassDB::bind_method(D_METHOD("send_message", "message", "data"), &EditorDebuggerPlugin::send_message);
	ClassDB::bind_method(D_METHOD("register_message_capture", "name", "callable"), &EditorDebuggerPlugin::register_message_capture);
	ClassDB::bind_method(D_METHOD("unregister_message_capture", "name"), &EditorDebuggerPlugin::unregister_message_capture);
	ClassDB::bind_method(D_METHOD("has_capture", "name"), &EditorDebuggerPlugin::has_capture);
	ClassDB::bind_method(D_METHOD("is_breaked"), &EditorDebuggerPlugin::is_breaked);
	ClassDB::bind_method(D_METHOD("is_debuggable"), &EditorDebuggerPlugin::is_debuggable);
	ClassDB::bind_method(D_METHOD("is_session_active"), &EditorDebuggerPlugin::is_session_active);

	ADD_SIGNAL(MethodInfo("started"));
	ADD_SIGNAL(MethodInfo("stopped"));
	ADD_SIGNAL(MethodInfo("breaked", PropertyInfo(Variant::BOOL, "can_debug")));
	ADD_SIGNAL(MethodInfo("continued"));
}

void EditorDebuggerPlugin::attach_debugger(ScriptEditorDebugger *p_debugger) {
	debugger = p_debugger;
	if (debugger) {
		debugger->connect("started", callable_mp(this, &EditorDebuggerPlugin::_started));
		debugger->connect("stopped", callable_mp(this, &EditorDebuggerPlugin::_stopped));
		debugger->connect("breaked", callable_mp(this, &EditorDebuggerPlugin::_breaked));
	}
}

void EditorDebuggerPlugin::detach_debugger(bool p_call_debugger) {
	if (debugger) {
		debugger->disconnect("started", callable_mp(this, &EditorDebuggerPlugin::_started));
		debugger->disconnect("stopped", callable_mp(this, &EditorDebuggerPlugin::_stopped));
		debugger->disconnect("breaked", callable_mp(this, &EditorDebuggerPlugin::_breaked));
		if (p_call_debugger && get_script_instance()) {
			debugger->remove_debugger_plugin(get_script_instance()->get_script());
		}
		debugger = nullptr;
	}
}

void EditorDebuggerPlugin::send_message(const String &p_message, const Array &p_args) {
	ERR_FAIL_COND_MSG(!debugger, "Plugin is not attached to debugger");
	debugger->send_message(p_message, p_args);
}

void EditorDebuggerPlugin::register_message_capture(const StringName &p_name, const Callable &p_callable) {
	ERR_FAIL_COND_MSG(!debugger, "Plugin is not attached to debugger");
	debugger->register_message_capture(p_name, p_callable);
}

void EditorDebuggerPlugin::unregister_message_capture(const StringName &p_name) {
	ERR_FAIL_COND_MSG(!debugger, "Plugin is not attached to debugger");
	debugger->unregister_message_capture(p_name);
}

bool EditorDebuggerPlugin::has_capture(const StringName &p_name) {
	ERR_FAIL_COND_V_MSG(!debugger, false, "Plugin is not attached to debugger");
	return debugger->has_capture(p_name);
}

bool EditorDebuggerPlugin::is_breaked() {
	ERR_FAIL_COND_V_MSG(!debugger, false, "Plugin is not attached to debugger");
	return debugger->is_breaked();
}

bool EditorDebuggerPlugin::is_debuggable() {
	ERR_FAIL_COND_V_MSG(!debugger, false, "Plugin is not attached to debugger");
	return debugger->is_debuggable();
}

bool EditorDebuggerPlugin::is_session_active() {
	ERR_FAIL_COND_V_MSG(!debugger, false, "Plugin is not attached to debugger");
	return debugger->is_session_active();
}

EditorDebuggerPlugin::~EditorDebuggerPlugin() {
	detach_debugger(true);
}
