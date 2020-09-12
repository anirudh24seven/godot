
/*  register_types.cpp                                                   */

#include "register_types.h"
#include "xr_interface_gdnative.h"

void register_xr_types() {
	ClassDB::register_class<XRInterfaceGDNative>();
	ClassDB::add_compatibility_class("ARVRInterfaceGDNative", "XRInterfaceGDNative");
}

void unregister_xr_types() {
}
