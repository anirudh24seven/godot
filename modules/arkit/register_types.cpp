
/*  register_types.cpp                                                   */



#include "register_types.h"

#include "arkit_interface.h"

void register_arkit_types() {
	// does it make sense to register the class?

	Ref<ARKitInterface> arkit_interface;
	arkit_interface.instance();
	XRServer::get_singleton()->add_interface(arkit_interface);
}

void unregister_arkit_types() {
	// should clean itself up nicely :)
}
