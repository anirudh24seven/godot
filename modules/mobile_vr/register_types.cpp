
/*  register_types.cpp                                                   */

#include "register_types.h"

#include "mobile_vr_interface.h"

void register_mobile_vr_types() {
	ClassDB::register_class<MobileVRInterface>();

	if (XRServer::get_singleton()) {
		Ref<MobileVRInterface> mobile_vr;
		mobile_vr.instance();
		XRServer::get_singleton()->add_interface(mobile_vr);
	}
}

void unregister_mobile_vr_types() {
}
