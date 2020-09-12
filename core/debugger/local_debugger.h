
/*  local_debugger.h                                                     */

#ifndef LOCAL_DEBUGGER_H
#define LOCAL_DEBUGGER_H

#include "core/debugger/engine_debugger.h"
#include "core/list.h"
#include "core/script_language.h"

class LocalDebugger : public EngineDebugger {
private:
	struct ScriptsProfiler;

	ScriptsProfiler *scripts_profiler = nullptr;

	String target_function;
	Map<String, String> options;

	Pair<String, int> to_breakpoint(const String &p_line);
	void print_variables(const List<String> &names, const List<Variant> &values, const String &variable_prefix);

public:
	void debug(bool p_can_continue, bool p_is_error_breakpoint);
	void send_message(const String &p_message, const Array &p_args);
	void send_error(const String &p_func, const String &p_file, int p_line, const String &p_err, const String &p_descr, ErrorHandlerType p_type);

	LocalDebugger();
	~LocalDebugger();
};

#endif // LOCAL_DEBUGGER_H
