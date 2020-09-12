
/*  editor_plugin_settings.h                                             */

#ifndef EDITORPLUGINSETTINGS_H
#define EDITORPLUGINSETTINGS_H

#include "core/undo_redo.h"
#include "editor/plugin_config_dialog.h"
#include "editor_data.h"
#include "property_editor.h"
#include "scene/gui/dialogs.h"

class EditorPluginSettings : public VBoxContainer {
	GDCLASS(EditorPluginSettings, VBoxContainer);

	enum {
		BUTTON_PLUGIN_EDIT
	};

	PluginConfigDialog *plugin_config_dialog;
	Button *create_plugin;
	Button *update_list;
	Tree *plugin_list;
	bool updating;

	void _plugin_activity_changed();
	void _create_clicked();
	void _cell_button_pressed(Object *p_item, int p_column, int p_id);

protected:
	void _notification(int p_what);

	static void _bind_methods();

public:
	void update_plugins();

	EditorPluginSettings();
};

#endif // EDITORPLUGINSETTINGS_H
