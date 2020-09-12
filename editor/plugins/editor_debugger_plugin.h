
/*  editor_debugger_plugin.h                                             */

#ifndef EDITOR_DEBUGGER_PLUGIN_H
#define EDITOR_DEBUGGER_PLUGIN_H

#include "scene/gui/control.h"

class ScriptEditorDebugger;

class EditorDebuggerPlugin : public Control {
	GDCLASS(EditorDebuggerPlugin, Control);

private:
	ScriptEditorDebugger *debugger = nullptr;

	void _breaked(bool p_really_did, bool p_can_debug);
	void _started();
	void _stopped();

protected:
	static void _bind_methods();

public:
	void attach_debugger(ScriptEditorDebugger *p_debugger);
	void detach_debugger(bool p_call_debugger);
	void send_message(const String &p_message, const Array &p_args);
	void register_message_capture(const StringName &p_name, const Callable &p_callable);
	void unregister_message_capture(const StringName &p_name);
	bool has_capture(const StringName &p_name);
	bool is_breaked();
	bool is_debuggable();
	bool is_session_active();
	~EditorDebuggerPlugin();
};

#endif // EDITOR_DEBUGGER_PLUGIN_H
