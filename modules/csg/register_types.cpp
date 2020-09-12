
/*  register_types.cpp                                                   */

#include "register_types.h"

#include "csg_gizmos.h"
#include "csg_shape.h"

void register_csg_types() {
#ifndef _3D_DISABLED

	ClassDB::register_virtual_class<CSGShape3D>();
	ClassDB::register_virtual_class<CSGPrimitive3D>();
	ClassDB::register_class<CSGMesh3D>();
	ClassDB::register_class<CSGSphere3D>();
	ClassDB::register_class<CSGBox3D>();
	ClassDB::register_class<CSGCylinder3D>();
	ClassDB::register_class<CSGTorus3D>();
	ClassDB::register_class<CSGPolygon3D>();
	ClassDB::register_class<CSGCombiner3D>();

#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<EditorPluginCSG>();
#endif
#endif
}

void unregister_csg_types() {
}
