
/*  project_settings_editor.h                                            */

#ifndef PROJECT_SETTINGS_EDITOR_H
#define PROJECT_SETTINGS_EDITOR_H

#include "core/undo_redo.h"
#include "editor/editor_data.h"
#include "editor/editor_plugin_settings.h"
#include "editor/editor_sectioned_inspector.h"
#include "editor/input_map_editor.h"
#include "editor/localization_editor.h"
#include "editor/shader_globals_editor.h"
#include "editor_autoload_settings.h"
#include "scene/gui/tab_container.h"

class ProjectSettingsEditor : public AcceptDialog {
	GDCLASS(ProjectSettingsEditor, AcceptDialog);

	enum InputType {
		INPUT_KEY,
		INPUT_KEY_PHYSICAL,
		INPUT_JOY_BUTTON,
		INPUT_JOY_MOTION,
		INPUT_MOUSE_BUTTON
	};

	static ProjectSettingsEditor *singleton;
	ProjectSettings *ps;
	Timer *timer;

	TabContainer *tab_container;
	SectionedInspector *inspector;
	InputMapEditor *inputmap_editor;
	LocalizationEditor *localization_editor;
	EditorAutoloadSettings *autoload_settings;
	ShaderGlobalsEditor *shaders_global_variables_editor;
	EditorPluginSettings *plugin_settings;

	HBoxContainer *search_bar;
	LineEdit *search_box;
	CheckButton *advanced;

	VBoxContainer *advanced_bar;
	LineEdit *category_box;
	LineEdit *property_box;
	Button *add_button;
	Button *del_button;
	OptionButton *type;
	OptionButton *feature_override;
	Label *error_label;

	ConfirmationDialog *del_confirmation;

	Label *restart_label;
	TextureRect *restart_icon;
	PanelContainer *restart_container;
	Button *restart_close_button;

	EditorData *data;
	UndoRedo *undo_redo;

	void _advanced_pressed();
	void _update_advanced_bar();
	void _text_field_changed(const String &p_text);
	void _feature_selected(int p_index);

	String _get_setting_name() const;
	void _setting_edited(const String &p_name);
	void _setting_selected(const String &p_path);
	void _add_setting();
	void _delete_setting(bool p_confirmed);

	void _editor_restart_request();
	void _editor_restart();
	void _editor_restart_close();

	void _add_feature_overrides();
	ProjectSettingsEditor();

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	static ProjectSettingsEditor *get_singleton() { return singleton; }
	void popup_project_settings();
	void set_plugins_page();
	void update_plugins();

	EditorAutoloadSettings *get_autoload_settings() { return autoload_settings; }
	TabContainer *get_tabs() { return tab_container; }

	void queue_save();

	ProjectSettingsEditor(EditorData *p_data);
};

#endif // PROJECT_SETTINGS_EDITOR_H
