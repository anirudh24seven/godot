
/*  multimesh_editor_plugin.h                                            */

#ifndef MULTIMESH_EDITOR_PLUGIN_H
#define MULTIMESH_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/3d/multimesh_instance_3d.h"
#include "scene/gui/spin_box.h"

class MultiMeshEditor : public Control {
	GDCLASS(MultiMeshEditor, Control);

	friend class MultiMeshEditorPlugin;

	AcceptDialog *err_dialog;
	MenuButton *options;
	MultiMeshInstance3D *_last_pp_node;
	bool browsing_source;

	Panel *panel;
	MultiMeshInstance3D *node;

	LineEdit *surface_source;
	LineEdit *mesh_source;

	SceneTreeDialog *std;

	ConfirmationDialog *populate_dialog;
	OptionButton *populate_axis;
	HSlider *populate_rotate_random;
	HSlider *populate_tilt_random;
	SpinBox *populate_scale_random;
	SpinBox *populate_scale;
	SpinBox *populate_amount;

	enum Menu {

		MENU_OPTION_POPULATE
	};

	void _browsed(const NodePath &p_path);
	void _menu_option(int);
	void _populate();
	void _browse(bool p_source);

protected:
	void _node_removed(Node *p_node);
	static void _bind_methods();

public:
	void edit(MultiMeshInstance3D *p_multimesh);
	MultiMeshEditor();
};

class MultiMeshEditorPlugin : public EditorPlugin {
	GDCLASS(MultiMeshEditorPlugin, EditorPlugin);

	MultiMeshEditor *multimesh_editor;
	EditorNode *editor;

public:
	virtual String get_name() const override { return "MultiMesh"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	MultiMeshEditorPlugin(EditorNode *p_node);
	~MultiMeshEditorPlugin();
};

#endif // MULTIMESH_EDITOR_PLUGIN_H
