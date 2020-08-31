
/*  property_selector.h                                                  */



#ifndef PROPERTYSELECTOR_H
#define PROPERTYSELECTOR_H

#include "editor/property_editor.h"
#include "editor_help.h"
#include "scene/gui/rich_text_label.h"

class PropertySelector : public ConfirmationDialog {
	GDCLASS(PropertySelector, ConfirmationDialog);

	LineEdit *search_box;
	Tree *search_options;

	void _text_changed(const String &p_newtext);
	void _sbox_input(const Ref<InputEvent> &p_ie);
	void _update_search();
	void _confirmed();
	void _item_selected();
	void _hide_requested();

	EditorHelpBit *help_bit;

	bool properties;
	String selected;
	Variant::Type type;
	String base_type;
	ObjectID script;
	Object *instance;
	bool virtuals_only;

	Vector<Variant::Type> type_filter;

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void select_method_from_base_type(const String &p_base, const String &p_current = "", bool p_virtuals_only = false);
	void select_method_from_script(const Ref<Script> &p_script, const String &p_current = "");
	void select_method_from_basic_type(Variant::Type p_type, const String &p_current = "");
	void select_method_from_instance(Object *p_instance, const String &p_current = "");

	void select_property_from_base_type(const String &p_base, const String &p_current = "");
	void select_property_from_script(const Ref<Script> &p_script, const String &p_current = "");
	void select_property_from_basic_type(Variant::Type p_type, const String &p_current = "");
	void select_property_from_instance(Object *p_instance, const String &p_current = "");

	void set_type_filter(const Vector<Variant::Type> &p_type_filter);

	PropertySelector();
};

#endif // PROPERTYSELECTOR_H
