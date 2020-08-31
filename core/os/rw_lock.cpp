
/*  rw_lock.cpp                                                          */



#include "rw_lock.h"

#include "core/error_macros.h"

#include <stddef.h>

RWLock *(*RWLock::create_func)() = nullptr;

RWLock *RWLock::create() {
	ERR_FAIL_COND_V(!create_func, nullptr);

	return create_func();
}
