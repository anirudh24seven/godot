
/*  callable.h                                                           */

#ifndef GODOT_CALLABLE_H
#define GODOT_CALLABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define GODOT_CALLABLE_SIZE (16)

#ifndef GODOT_CORE_API_GODOT_CALLABLE_TYPE_DEFINED
#define GODOT_CORE_API_GODOT_CALLABLE_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[GODOT_CALLABLE_SIZE];
} godot_callable;
#endif

#define GODOT_SIGNAL_SIZE (16)

#ifndef GODOT_CORE_API_GODOT_SIGNAL_TYPE_DEFINED
#define GODOT_CORE_API_GODOT_SIGNAL_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[GODOT_SIGNAL_SIZE];
} godot_signal;
#endif

#ifdef __cplusplus
}
#endif

#include <gdnative/gdnative.h>
#include <gdnative/string_name.h>

#ifdef __cplusplus
extern "C" {
#endif

// Callable

void GDAPI godot_callable_new_with_object(godot_callable *r_dest, const godot_object *p_object, const godot_string_name *p_method);
void GDAPI godot_callable_new_with_object_id(godot_callable *r_dest, uint64_t p_objectid, const godot_string_name *p_method);
void GDAPI godot_callable_new_copy(godot_callable *r_dest, const godot_callable *p_src);

void GDAPI godot_callable_destroy(godot_callable *p_self);

godot_int GDAPI godot_callable_call(const godot_callable *p_self, const godot_variant **p_arguments, godot_int p_argcount, godot_variant *r_return_value);
void GDAPI godot_callable_call_deferred(const godot_callable *p_self, const godot_variant **p_arguments, godot_int p_argcount);

godot_bool GDAPI godot_callable_is_null(const godot_callable *p_self);
godot_bool GDAPI godot_callable_is_custom(const godot_callable *p_self);
godot_bool GDAPI godot_callable_is_standard(const godot_callable *p_self);

godot_object GDAPI *godot_callable_get_object(const godot_callable *p_self);
uint64_t GDAPI godot_callable_get_object_id(const godot_callable *p_self);
godot_string_name GDAPI godot_callable_get_method(const godot_callable *p_self);

uint32_t GDAPI godot_callable_hash(const godot_callable *p_self);

godot_string GDAPI godot_callable_as_string(const godot_callable *p_self);

godot_bool GDAPI godot_callable_operator_equal(const godot_callable *p_self, const godot_callable *p_other);
godot_bool GDAPI godot_callable_operator_less(const godot_callable *p_self, const godot_callable *p_other);

// Signal

void GDAPI godot_signal_new_with_object(godot_signal *r_dest, const godot_object *p_object, const godot_string_name *p_name);
void GDAPI godot_signal_new_with_object_id(godot_signal *r_dest, uint64_t p_objectid, const godot_string_name *p_name);
void GDAPI godot_signal_new_copy(godot_signal *r_dest, const godot_signal *p_src);

void GDAPI godot_signal_destroy(godot_signal *p_self);

godot_int GDAPI godot_signal_emit(const godot_signal *p_self, const godot_variant **p_arguments, godot_int p_argcount);

godot_int GDAPI godot_signal_connect(godot_signal *p_self, const godot_callable *p_callable, const godot_array *p_binds, uint32_t p_flags);
void GDAPI godot_signal_disconnect(godot_signal *p_self, const godot_callable *p_callable);

godot_bool GDAPI godot_signal_is_null(const godot_signal *p_self);
godot_bool GDAPI godot_signal_is_connected(const godot_signal *p_self, const godot_callable *p_callable);

godot_array GDAPI godot_signal_get_connections(const godot_signal *p_self);

godot_object GDAPI *godot_signal_get_object(const godot_signal *p_self);
uint64_t GDAPI godot_signal_get_object_id(const godot_signal *p_self);
godot_string_name GDAPI godot_signal_get_name(const godot_signal *p_self);

godot_string GDAPI godot_signal_as_string(const godot_signal *p_self);

godot_bool GDAPI godot_signal_operator_equal(const godot_signal *p_self, const godot_signal *p_other);
godot_bool GDAPI godot_signal_operator_less(const godot_signal *p_self, const godot_signal *p_other);

#ifdef __cplusplus
}
#endif

#endif
