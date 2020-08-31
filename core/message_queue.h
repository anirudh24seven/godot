
/*  message_queue.h                                                      */



#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "core/object.h"
#include "core/os/thread_safe.h"

class MessageQueue {
	_THREAD_SAFE_CLASS_

	enum {

		DEFAULT_QUEUE_SIZE_KB = 1024
	};

	enum {
		TYPE_CALL,
		TYPE_NOTIFICATION,
		TYPE_SET,
		FLAG_SHOW_ERROR = 1 << 14,
		FLAG_MASK = FLAG_SHOW_ERROR - 1

	};

	struct Message {
		Callable callable;
		int16_t type;
		union {
			int16_t notification;
			int16_t args;
		};
	};

	uint8_t *buffer;
	uint32_t buffer_end = 0;
	uint32_t buffer_max_used = 0;
	uint32_t buffer_size;

	void _call_function(const Callable &p_callable, const Variant *p_args, int p_argcount, bool p_show_error);

	static MessageQueue *singleton;

	bool flushing = false;

public:
	static MessageQueue *get_singleton();

	Error push_call(ObjectID p_id, const StringName &p_method, const Variant **p_args, int p_argcount, bool p_show_error = false);
	Error push_call(ObjectID p_id, const StringName &p_method, VARIANT_ARG_LIST);
	Error push_notification(ObjectID p_id, int p_notification);
	Error push_set(ObjectID p_id, const StringName &p_prop, const Variant &p_value);
	Error push_callable(const Callable &p_callable, const Variant **p_args, int p_argcount, bool p_show_error = false);
	Error push_callable(const Callable &p_callable, VARIANT_ARG_LIST);

	Error push_call(Object *p_object, const StringName &p_method, VARIANT_ARG_LIST);
	Error push_notification(Object *p_object, int p_notification);
	Error push_set(Object *p_object, const StringName &p_prop, const Variant &p_value);

	void statistics();
	void flush();

	bool is_flushing() const;

	int get_max_buffer_usage() const;

	MessageQueue();
	~MessageQueue();
};

#endif // MESSAGE_QUEUE_H
