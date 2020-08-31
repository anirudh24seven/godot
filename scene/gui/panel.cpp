
/*  panel.cpp                                                            */



#include "panel.h"

#include "core/print_string.h"

void Panel::_notification(int p_what) {
	if (p_what == NOTIFICATION_DRAW) {
		RID ci = get_canvas_item();
		Ref<StyleBox> style = mode == MODE_BACKGROUND ? get_theme_stylebox("panel") : get_theme_stylebox("panel_fg");
		style->draw(ci, Rect2(Point2(), get_size()));
	}
}

void Panel::set_mode(Mode p_mode) {
	mode = p_mode;
	update();
}

Panel::Mode Panel::get_mode() const {
	return mode;
}

void Panel::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_mode", "mode"), &Panel::set_mode);
	ClassDB::bind_method(D_METHOD("get_mode"), &Panel::get_mode);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "mode", PROPERTY_HINT_ENUM, "Background,Foreground"), "set_mode", "get_mode");

	BIND_ENUM_CONSTANT(MODE_BACKGROUND);
	BIND_ENUM_CONSTANT(MODE_FOREGROUND);
}

Panel::Panel() {
	// Has visible stylebox, so stop by default.
	set_mouse_filter(MOUSE_FILTER_STOP);
}

Panel::~Panel() {
}
