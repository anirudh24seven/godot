
/*  func_ref.cpp                                                         */

#include "func_ref.h"

Variant FuncRef::call_func(const Variant **p_args, int p_argcount, Callable::CallError &r_error) {
	if (id.is_null()) {
		r_error.error = Callable::CallError::CALL_ERROR_INSTANCE_IS_NULL;
		return Variant();
	}
	Object *obj = ObjectDB::get_instance(id);

	if (!obj) {
		r_error.error = Callable::CallError::CALL_ERROR_INSTANCE_IS_NULL;
		return Variant();
	}

	return obj->call(function, p_args, p_argcount, r_error);
}

Variant FuncRef::call_funcv(const Array &p_args) {
	ERR_FAIL_COND_V(id.is_null(), Variant());

	Object *obj = ObjectDB::get_instance(id);

	ERR_FAIL_COND_V(!obj, Variant());

	return obj->callv(function, p_args);
}

void FuncRef::set_instance(Object *p_obj) {
	ERR_FAIL_NULL(p_obj);
	id = p_obj->get_instance_id();
}

void FuncRef::set_function(const StringName &p_func) {
	function = p_func;
}

bool FuncRef::is_valid() const {
	if (id.is_null()) {
		return false;
	}

	Object *obj = ObjectDB::get_instance(id);
	if (!obj) {
		return false;
	}

	return obj->has_method(function);
}

void FuncRef::_bind_methods() {
	{
		MethodInfo mi;
		mi.name = "call_func";
		Vector<Variant> defargs;
		ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "call_func", &FuncRef::call_func, mi, defargs);
	}

	ClassDB::bind_method(D_METHOD("call_funcv", "arg_array"), &FuncRef::call_funcv);

	ClassDB::bind_method(D_METHOD("set_instance", "instance"), &FuncRef::set_instance);
	ClassDB::bind_method(D_METHOD("set_function", "name"), &FuncRef::set_function);
	ClassDB::bind_method(D_METHOD("is_valid"), &FuncRef::is_valid);
}
