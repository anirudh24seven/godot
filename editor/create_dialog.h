
/*  create_dialog.h                                                      */

#ifndef CREATE_DIALOG_H
#define CREATE_DIALOG_H

#include "editor_help.h"
#include "scene/gui/button.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/item_list.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/tree.h"

class CreateDialog : public ConfirmationDialog {
	GDCLASS(CreateDialog, ConfirmationDialog);

	LineEdit *search_box;
	Tree *search_options;

	String base_type;
	String icon_fallback;
	String preferred_search_result_type;

	Button *favorite;
	Vector<String> favorite_list;
	Tree *favorites;
	ItemList *recent;
	EditorHelpBit *help_bit;

	HashMap<String, TreeItem *> search_options_types;
	HashMap<String, String> custom_type_parents;
	HashMap<String, int> custom_type_indices;
	List<StringName> type_list;
	Set<StringName> type_blacklist;

	void _update_search();
	bool _should_hide_type(const String &p_type) const;
	void _add_type(const String &p_current, bool p_cpp_type);
	void _configure_search_option_item(TreeItem *r_item, const String &p_type, const bool p_cpp_type);
	String _top_result(const Vector<String> p_candidates, const String &p_search_text) const;
	float _score_type(const String &p_type, const String &p_search) const;
	bool _is_type_preferred(const String &p_type) const;

	void _fill_type_list();
	void _cleanup();

	void _sbox_input(const Ref<InputEvent> &p_ie);
	void _text_changed(const String &p_newtext);
	void select_type(const String &p_type);
	void _item_selected();
	void _hide_requested();

	void _confirmed();
	virtual void cancel_pressed() override;

	void _favorite_toggled();

	void _history_selected(int p_idx);
	void _favorite_selected();

	void _history_activated(int p_idx);
	void _favorite_activated();

	Variant get_drag_data_fw(const Point2 &p_point, Control *p_from);
	bool can_drop_data_fw(const Point2 &p_point, const Variant &p_data, Control *p_from) const;
	void drop_data_fw(const Point2 &p_point, const Variant &p_data, Control *p_from);

	bool _is_class_disabled_by_feature_profile(const StringName &p_class) const;
	void _load_favorites_and_history();

protected:
	void _notification(int p_what);
	static void _bind_methods();

	void _save_and_update_favorite_list();

public:
	Object *instance_selected();
	String get_selected_type();

	void set_base_type(const String &p_base) { base_type = p_base; }
	String get_base_type() const { return base_type; }

	void set_preferred_search_result_type(const String &p_preferred_type) { preferred_search_result_type = p_preferred_type; }
	String get_preferred_search_result_type() { return preferred_search_result_type; }

	void popup_create(bool p_dont_clear, bool p_replace_mode = false, const String &p_select_type = "Node");

	CreateDialog();
};

#endif
