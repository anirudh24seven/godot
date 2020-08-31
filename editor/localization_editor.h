
/*  localization_editor.h                                                */



#ifndef LOCALIZATION_EDITOR_H
#define LOCALIZATION_EDITOR_H

#include "core/undo_redo.h"
#include "editor_file_dialog.h"
#include "scene/gui/tree.h"

class LocalizationEditor : public VBoxContainer {
	GDCLASS(LocalizationEditor, VBoxContainer);

	enum LocaleFilter {
		SHOW_ALL_LOCALES,
		SHOW_ONLY_SELECTED_LOCALES,
	};

	Tree *translation_list;

	EditorFileDialog *translation_file_open;

	Button *translation_res_option_add_button;
	EditorFileDialog *translation_res_file_open_dialog;
	EditorFileDialog *translation_res_option_file_open_dialog;
	Tree *translation_remap;
	Tree *translation_remap_options;
	Tree *translation_filter;
	bool translation_locales_list_created;
	OptionButton *translation_locale_filter_mode;
	Vector<TreeItem *> translation_filter_treeitems;
	Vector<int> translation_locales_idxs_remap;

	Tree *translation_pot_list;
	EditorFileDialog *pot_file_open_dialog;
	EditorFileDialog *pot_generate_dialog;

	UndoRedo *undo_redo;
	bool updating_translations;
	String localization_changed;

	void _translation_file_open();
	void _translation_add(const String &p_path);
	void _translation_delete(Object *p_item, int p_column, int p_button);

	void _translation_res_file_open();
	void _translation_res_add(const String &p_path);
	void _translation_res_delete(Object *p_item, int p_column, int p_button);
	void _translation_res_select();
	void _translation_res_option_file_open();
	void _translation_res_option_add(const String &p_path);
	void _translation_res_option_changed();
	void _translation_res_option_delete(Object *p_item, int p_column, int p_button);

	void _translation_filter_option_changed();
	void _translation_filter_mode_changed(int p_mode);

	void _pot_add(const String &p_path);
	void _pot_delete(Object *p_item, int p_column, int p_button);
	void _pot_file_open();
	void _pot_generate_open();
	void _pot_generate(const String &p_file);
	void _update_pot_file_extensions();

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void add_translation(const String &p_translation);
	void update_translations();

	LocalizationEditor();
};

#endif // LOCALIZATION_EDITOR_H
