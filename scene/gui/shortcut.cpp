
/*  shortcut.cpp                                                         */

#include "shortcut.h"

#include "core/os/keyboard.h"

void Shortcut::set_shortcut(const Ref<InputEvent> &p_shortcut) {
	shortcut = p_shortcut;
	emit_changed();
}

Ref<InputEvent> Shortcut::get_shortcut() const {
	return shortcut;
}

bool Shortcut::is_shortcut(const Ref<InputEvent> &p_event) const {
	return shortcut.is_valid() && shortcut->shortcut_match(p_event);
}

String Shortcut::get_as_text() const {
	if (shortcut.is_valid()) {
		return shortcut->as_text();
	} else {
		return "None";
	}
}

bool Shortcut::is_valid() const {
	return shortcut.is_valid();
}

void Shortcut::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_shortcut", "event"), &Shortcut::set_shortcut);
	ClassDB::bind_method(D_METHOD("get_shortcut"), &Shortcut::get_shortcut);

	ClassDB::bind_method(D_METHOD("is_valid"), &Shortcut::is_valid);

	ClassDB::bind_method(D_METHOD("is_shortcut", "event"), &Shortcut::is_shortcut);
	ClassDB::bind_method(D_METHOD("get_as_text"), &Shortcut::get_as_text);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "shortcut", PROPERTY_HINT_RESOURCE_TYPE, "InputEvent"), "set_shortcut", "get_shortcut");
}

Shortcut::Shortcut() {
}
