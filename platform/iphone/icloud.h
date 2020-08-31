
/*  icloud.h                                                             */



#ifdef ICLOUD_ENABLED

#ifndef ICLOUD_H
#define ICLOUD_H

#include "core/object.h"

class ICloud : public Object {
	GDCLASS(ICloud, Object);

	static ICloud *instance;
	static void _bind_methods();

	List<Variant> pending_events;

public:
	Error remove_key(String p_param);
	Array set_key_values(Dictionary p_params);
	Variant get_key_value(String p_param);
	Error synchronize_key_values();
	Variant get_all_key_values();

	int get_pending_event_count();
	Variant pop_pending_event();

	static ICloud *get_singleton();

	ICloud();
	~ICloud();
};

#endif

#endif
