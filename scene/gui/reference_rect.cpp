
/*  reference_rect.cpp                                                   */

#include "reference_rect.h"

#include "core/engine.h"

void ReferenceRect::_notification(int p_what) {
	if (p_what == NOTIFICATION_DRAW) {
		if (!is_inside_tree()) {
			return;
		}
		if (Engine::get_singleton()->is_editor_hint() || !editor_only) {
			draw_rect(Rect2(Point2(), get_size()), border_color, false);
		}
	}
}

void ReferenceRect::set_border_color(const Color &p_color) {
	border_color = p_color;
	update();
}

Color ReferenceRect::get_border_color() const {
	return border_color;
}

void ReferenceRect::set_editor_only(const bool &p_enabled) {
	editor_only = p_enabled;
	update();
}

bool ReferenceRect::get_editor_only() const {
	return editor_only;
}

void ReferenceRect::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_border_color"), &ReferenceRect::get_border_color);
	ClassDB::bind_method(D_METHOD("set_border_color", "color"), &ReferenceRect::set_border_color);

	ClassDB::bind_method(D_METHOD("get_editor_only"), &ReferenceRect::get_editor_only);
	ClassDB::bind_method(D_METHOD("set_editor_only", "enabled"), &ReferenceRect::set_editor_only);

	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "border_color"), "set_border_color", "get_border_color");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "editor_only"), "set_editor_only", "get_editor_only");
}

ReferenceRect::ReferenceRect() {
	border_color = Color(1, 0, 0);
	editor_only = true;
}
