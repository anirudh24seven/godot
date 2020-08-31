
/*  navigation_mesh_editor_plugin.h                                      */



#ifndef NAVIGATION_MESH_EDITOR_PLUGIN_H
#define NAVIGATION_MESH_EDITOR_PLUGIN_H

#ifdef TOOLS_ENABLED

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"

class NavigationRegion3D;

class NavigationMeshEditor : public Control {
	friend class NavigationMeshEditorPlugin;

	GDCLASS(NavigationMeshEditor, Control);

	AcceptDialog *err_dialog;

	HBoxContainer *bake_hbox;
	Button *button_bake;
	Button *button_reset;
	Label *bake_info;

	NavigationRegion3D *node;

	void _bake_pressed();
	void _clear_pressed();

protected:
	void _node_removed(Node *p_node);
	static void _bind_methods();
	void _notification(int p_option);

public:
	void edit(NavigationRegion3D *p_nav_region);
	NavigationMeshEditor();
	~NavigationMeshEditor();
};

class NavigationMeshEditorPlugin : public EditorPlugin {
	GDCLASS(NavigationMeshEditorPlugin, EditorPlugin);

	NavigationMeshEditor *navigation_mesh_editor;
	EditorNode *editor;

public:
	virtual String get_name() const override { return "NavigationMesh"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	NavigationMeshEditorPlugin(EditorNode *p_node);
	~NavigationMeshEditorPlugin();
};

#endif

#endif
