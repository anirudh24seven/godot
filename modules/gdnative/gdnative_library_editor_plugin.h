
/*  gdnative_library_editor_plugin.h                                     */



#ifndef GDNATIVE_LIBRARY_EDITOR_PLUGIN_H
#define GDNATIVE_LIBRARY_EDITOR_PLUGIN_H

#ifdef TOOLS_ENABLED
#include "editor/editor_node.h"
#include "gdnative.h"

class GDNativeLibraryEditor : public Control {
	GDCLASS(GDNativeLibraryEditor, Control);

	struct NativePlatformConfig {
		String name;
		String library_extension;
		List<String> entries;
	};

	struct TargetConfig {
		String library;
		Array dependencies;
	};

	enum ItemButton {
		BUTTON_SELECT_LIBRARY,
		BUTTON_CLEAR_LIBRARY,
		BUTTON_SELECT_DEPENDENCES,
		BUTTON_CLEAR_DEPENDENCES,
		BUTTON_ERASE_ENTRY,
		BUTTON_MOVE_UP,
		BUTTON_MOVE_DOWN,
	};

	Tree *tree;
	MenuButton *filter;
	EditorFileDialog *file_dialog;
	ConfirmationDialog *new_architecture_dialog;
	LineEdit *new_architecture_input;
	Set<String> collapsed_items;

	String showing_platform;
	Ref<GDNativeLibrary> library;
	Map<String, NativePlatformConfig> platforms;
	Map<String, TargetConfig> entry_configs;

protected:
	static void _bind_methods();
	void _update_tree();
	void _on_item_button(Object *item, int column, int id);
	void _on_library_selected(const String &file);
	void _on_dependencies_selected(const PackedStringArray &files);
	void _on_filter_selected(int id);
	void _on_item_collapsed(Object *p_item);
	void _on_item_activated();
	void _on_create_new_entry();
	void _set_target_value(const String &section, const String &target, Variant file);
	void _erase_entry(const String &platform, const String &entry);
	void _move_entry(const String &platform, const String &entry, int dir);
	void _translate_to_config_file();

public:
	void edit(Ref<GDNativeLibrary> p_library);

	GDNativeLibraryEditor();
};

class GDNativeLibraryEditorPlugin : public EditorPlugin {
	GDCLASS(GDNativeLibraryEditorPlugin, EditorPlugin);

	GDNativeLibraryEditor *library_editor;
	EditorNode *editor;
	Button *button;

public:
	virtual String get_name() const override { return "GDNativeLibrary"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_node) override;
	virtual bool handles(Object *p_node) const override;
	virtual void make_visible(bool p_visible) override;

	GDNativeLibraryEditorPlugin(EditorNode *p_node);
};
#endif
#endif // GDNATIVE_LIBRARY_EDITOR_PLUGIN_H
