
/*  javascript_eval.h                                                    */

#ifndef JAVASCRIPT_EVAL_H
#define JAVASCRIPT_EVAL_H

#include "core/object.h"

class JavaScript : public Object {
private:
	GDCLASS(JavaScript, Object);

	static JavaScript *singleton;

protected:
	static void _bind_methods();

public:
	Variant eval(const String &p_code, bool p_use_global_exec_context = false);

	static JavaScript *get_singleton();
	JavaScript();
	~JavaScript();
};

#endif // JAVASCRIPT_EVAL_H
