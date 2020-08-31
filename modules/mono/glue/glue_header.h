
/*  glue_header.h                                                        */



#ifdef MONO_GLUE_ENABLED

#include "../mono_gd/gd_mono_marshal.h"

void godot_register_collections_icalls();
void godot_register_gd_icalls();
void godot_register_string_name_icalls();
void godot_register_nodepath_icalls();
void godot_register_object_icalls();
void godot_register_rid_icalls();
void godot_register_string_icalls();
void godot_register_scene_tree_icalls();

/**
 * Registers internal calls that were not generated. This function is called
 * from the generated GodotSharpBindings::register_generated_icalls() function.
 */
void godot_register_glue_header_icalls() {
	godot_register_collections_icalls();
	godot_register_gd_icalls();
	godot_register_string_name_icalls();
	godot_register_nodepath_icalls();
	godot_register_object_icalls();
	godot_register_rid_icalls();
	godot_register_string_icalls();
	godot_register_scene_tree_icalls();
}

// Used by the generated glue

#include "core/array.h"
#include "core/class_db.h"
#include "core/dictionary.h"
#include "core/engine.h"
#include "core/method_bind.h"
#include "core/node_path.h"
#include "core/object.h"
#include "core/reference.h"
#include "core/typedefs.h"
#include "core/ustring.h"

#include "../mono_gd/gd_mono_class.h"
#include "../mono_gd/gd_mono_internals.h"
#include "../mono_gd/gd_mono_utils.h"

#define GODOTSHARP_INSTANCE_OBJECT(m_instance, m_type) \
	static ClassDB::ClassInfo *ci = nullptr;           \
	if (!ci) {                                         \
		ci = ClassDB::classes.getptr(m_type);          \
	}                                                  \
	Object *m_instance = ci->creation_func();

#include "arguments_vector.h"

#endif // MONO_GLUE_ENABLED
