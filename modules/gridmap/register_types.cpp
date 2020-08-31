
/*  register_types.cpp                                                   */



#include "register_types.h"
#ifndef _3D_DISABLED
#include "core/class_db.h"
#include "grid_map.h"
#include "grid_map_editor_plugin.h"
#endif

void register_gridmap_types() {
#ifndef _3D_DISABLED
	ClassDB::register_class<GridMap>();
#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<GridMapEditorPlugin>();
#endif
#endif
}

void unregister_gridmap_types() {
}
