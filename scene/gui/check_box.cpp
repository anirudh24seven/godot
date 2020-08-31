
/*  check_box.cpp                                                        */



#include "check_box.h"

#include "servers/rendering_server.h"

Size2 CheckBox::get_icon_size() const {
	Ref<Texture2D> checked = Control::get_theme_icon("checked");
	Ref<Texture2D> unchecked = Control::get_theme_icon("unchecked");
	Ref<Texture2D> radio_checked = Control::get_theme_icon("radio_checked");
	Ref<Texture2D> radio_unchecked = Control::get_theme_icon("radio_unchecked");

	Size2 tex_size = Size2(0, 0);
	if (!checked.is_null()) {
		tex_size = Size2(checked->get_width(), checked->get_height());
	}
	if (!unchecked.is_null()) {
		tex_size = Size2(MAX(tex_size.width, unchecked->get_width()), MAX(tex_size.height, unchecked->get_height()));
	}
	if (!radio_checked.is_null()) {
		tex_size = Size2(MAX(tex_size.width, radio_checked->get_width()), MAX(tex_size.height, radio_checked->get_height()));
	}
	if (!radio_unchecked.is_null()) {
		tex_size = Size2(MAX(tex_size.width, radio_unchecked->get_width()), MAX(tex_size.height, radio_unchecked->get_height()));
	}
	return tex_size;
}

Size2 CheckBox::get_minimum_size() const {
	Size2 minsize = Button::get_minimum_size();
	Size2 tex_size = get_icon_size();
	minsize.width += tex_size.width;
	if (get_text().length() > 0) {
		minsize.width += get_theme_constant("hseparation");
	}
	Ref<StyleBox> sb = get_theme_stylebox("normal");
	minsize.height = MAX(minsize.height, tex_size.height + sb->get_margin(MARGIN_TOP) + sb->get_margin(MARGIN_BOTTOM));

	return minsize;
}

void CheckBox::_notification(int p_what) {
	if (p_what == NOTIFICATION_THEME_CHANGED) {
		_set_internal_margin(MARGIN_LEFT, get_icon_size().width);
	} else if (p_what == NOTIFICATION_DRAW) {
		RID ci = get_canvas_item();

		Ref<Texture2D> on = Control::get_theme_icon(is_radio() ? "radio_checked" : "checked");
		Ref<Texture2D> off = Control::get_theme_icon(is_radio() ? "radio_unchecked" : "unchecked");
		Ref<StyleBox> sb = get_theme_stylebox("normal");

		Vector2 ofs;
		ofs.x = sb->get_margin(MARGIN_LEFT);
		ofs.y = int((get_size().height - get_icon_size().height) / 2) + get_theme_constant("check_vadjust");

		if (is_pressed()) {
			on->draw(ci, ofs);
		} else {
			off->draw(ci, ofs);
		}
	}
}

bool CheckBox::is_radio() {
	return get_button_group().is_valid();
}

CheckBox::CheckBox(const String &p_text) :
		Button(p_text) {
	set_toggle_mode(true);
	set_text_align(ALIGN_LEFT);
	_set_internal_margin(MARGIN_LEFT, get_icon_size().width);
}

CheckBox::~CheckBox() {
}
