
/*  nodepath_glue.cpp                                                    */



#ifdef MONO_GLUE_ENABLED

#include "core/node_path.h"
#include "core/ustring.h"

#include "../mono_gd/gd_mono_marshal.h"

NodePath *godot_icall_NodePath_Ctor(MonoString *p_path) {
	return memnew(NodePath(GDMonoMarshal::mono_string_to_godot(p_path)));
}

void godot_icall_NodePath_Dtor(NodePath *p_ptr) {
	ERR_FAIL_NULL(p_ptr);
	memdelete(p_ptr);
}

MonoString *godot_icall_NodePath_operator_String(NodePath *p_np) {
	return GDMonoMarshal::mono_string_from_godot(p_np->operator String());
}

MonoBoolean godot_icall_NodePath_is_absolute(NodePath *p_ptr) {
	return (MonoBoolean)p_ptr->is_absolute();
}

int32_t godot_icall_NodePath_get_name_count(NodePath *p_ptr) {
	return p_ptr->get_name_count();
}

MonoString *godot_icall_NodePath_get_name(NodePath *p_ptr, uint32_t p_idx) {
	return GDMonoMarshal::mono_string_from_godot(p_ptr->get_name(p_idx));
}

int32_t godot_icall_NodePath_get_subname_count(NodePath *p_ptr) {
	return p_ptr->get_subname_count();
}

MonoString *godot_icall_NodePath_get_subname(NodePath *p_ptr, uint32_t p_idx) {
	return GDMonoMarshal::mono_string_from_godot(p_ptr->get_subname(p_idx));
}

MonoString *godot_icall_NodePath_get_concatenated_subnames(NodePath *p_ptr) {
	return GDMonoMarshal::mono_string_from_godot(p_ptr->get_concatenated_subnames());
}

NodePath *godot_icall_NodePath_get_as_property_path(NodePath *p_ptr) {
	return memnew(NodePath(p_ptr->get_as_property_path()));
}

MonoBoolean godot_icall_NodePath_is_empty(NodePath *p_ptr) {
	return (MonoBoolean)p_ptr->is_empty();
}

void godot_register_nodepath_icalls() {
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_Ctor", (void *)godot_icall_NodePath_Ctor);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_Dtor", (void *)godot_icall_NodePath_Dtor);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_operator_String", (void *)godot_icall_NodePath_operator_String);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_get_as_property_path", (void *)godot_icall_NodePath_get_as_property_path);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_get_concatenated_subnames", (void *)godot_icall_NodePath_get_concatenated_subnames);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_get_name", (void *)godot_icall_NodePath_get_name);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_get_name_count", (void *)godot_icall_NodePath_get_name_count);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_get_subname", (void *)godot_icall_NodePath_get_subname);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_get_subname_count", (void *)godot_icall_NodePath_get_subname_count);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_is_absolute", (void *)godot_icall_NodePath_is_absolute);
	mono_add_internal_call("Godot.NodePath::godot_icall_NodePath_is_empty", (void *)godot_icall_NodePath_is_empty);
}

#endif // MONO_GLUE_ENABLED
