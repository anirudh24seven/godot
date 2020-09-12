
/*  api.cpp                                                              */

#include "api.h"
#include "core/engine.h"
#include "javascript_eval.h"

static JavaScript *javascript_eval;

void register_javascript_api() {
	ClassDB::register_virtual_class<JavaScript>();
	javascript_eval = memnew(JavaScript);
	Engine::get_singleton()->add_singleton(Engine::Singleton("JavaScript", javascript_eval));
}

void unregister_javascript_api() {
	memdelete(javascript_eval);
}

JavaScript *JavaScript::singleton = nullptr;

JavaScript *JavaScript::get_singleton() {
	return singleton;
}

JavaScript::JavaScript() {
	ERR_FAIL_COND_MSG(singleton != nullptr, "JavaScript singleton already exist.");
	singleton = this;
}

JavaScript::~JavaScript() {}

void JavaScript::_bind_methods() {
	ClassDB::bind_method(D_METHOD("eval", "code", "use_global_execution_context"), &JavaScript::eval, DEFVAL(false));
}

#if !defined(JAVASCRIPT_ENABLED) || !defined(JAVASCRIPT_EVAL_ENABLED)
Variant JavaScript::eval(const String &p_code, bool p_use_global_exec_context) {
	return Variant();
}
#endif
