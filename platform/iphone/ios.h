
/*  ios.h                                                                */

#ifndef IOS_H
#define IOS_H

#include "core/object.h"

class iOS : public Object {
	GDCLASS(iOS, Object);

	static void _bind_methods();

public:
	static void alert(const char *p_alert, const char *p_title);

	String get_model() const;
	String get_rate_url(int p_app_id) const;

	iOS();
};

#endif
