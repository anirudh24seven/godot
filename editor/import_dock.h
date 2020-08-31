
/*  import_dock.h                                                        */



#ifndef IMPORTDOCK_H
#define IMPORTDOCK_H

#include "core/io/config_file.h"
#include "core/io/resource_importer.h"
#include "editor/editor_file_system.h"
#include "editor/editor_inspector.h"
#include "scene/gui/box_container.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/option_button.h"
#include "scene/gui/popup_menu.h"

class ImportDockParameters;
class ImportDock : public VBoxContainer {
	GDCLASS(ImportDock, VBoxContainer);

	Label *imported;
	OptionButton *import_as;
	MenuButton *preset;
	EditorInspector *import_opts;

	List<PropertyInfo> properties;
	Map<StringName, Variant> property_values;

	ConfirmationDialog *reimport_confirm;
	Label *label_warning;
	Button *import;

	ImportDockParameters *params;

	void _preset_selected(int p_idx);
	void _importer_selected(int i_idx);
	void _update_options(const Ref<ConfigFile> &p_config = Ref<ConfigFile>());
	void _update_preset_menu();

	void _property_toggled(const StringName &p_prop, bool p_checked);
	void _reimport_attempt();
	void _reimport_and_restart();
	void _reimport();

	enum {
		ITEM_SET_AS_DEFAULT = 100,
		ITEM_LOAD_DEFAULT,
		ITEM_CLEAR_DEFAULT,
	};

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	void set_edit_path(const String &p_path);
	void set_edit_multiple_paths(const Vector<String> &p_paths);
	void initialize_import_options() const;
	void clear();

	ImportDock();
	~ImportDock();
};

#endif // IMPORTDOCK_H
