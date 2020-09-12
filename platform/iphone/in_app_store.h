
/*  in_app_store.h                                                       */

#ifdef STOREKIT_ENABLED

#ifndef IN_APP_STORE_H
#define IN_APP_STORE_H

#include "core/object.h"

class InAppStore : public Object {
	GDCLASS(InAppStore, Object);

	static InAppStore *instance;
	static void _bind_methods();

	List<Variant> pending_events;

public:
	Error request_product_info(Dictionary p_params);
	Error restore_purchases();
	Error purchase(Dictionary p_params);

	int get_pending_event_count();
	Variant pop_pending_event();
	void finish_transaction(String product_id);
	void set_auto_finish_transaction(bool b);

	void _post_event(Variant p_event);
	void _record_purchase(String product_id);

	static InAppStore *get_singleton();

	InAppStore();
	~InAppStore();
};

#endif

#endif
