
/*  physical_bone_3d_editor_plugin.h                                     */

#ifndef PHYSICAL_BONE_PLUGIN_H
#define PHYSICAL_BONE_PLUGIN_H

#include "editor/editor_node.h"

class PhysicalBone3DEditor : public Object {
	GDCLASS(PhysicalBone3DEditor, Object);

	EditorNode *editor;
	HBoxContainer *spatial_editor_hb;
	Button *button_transform_joint;

	PhysicalBone3D *selected = nullptr;

protected:
	static void _bind_methods();

private:
	void _on_toggle_button_transform_joint(bool p_is_pressed);
	void _set_move_joint();

public:
	PhysicalBone3DEditor(EditorNode *p_editor);
	~PhysicalBone3DEditor() {}

	void set_selected(PhysicalBone3D *p_pb);

	void hide();
	void show();
};

class PhysicalBone3DEditorPlugin : public EditorPlugin {
	GDCLASS(PhysicalBone3DEditorPlugin, EditorPlugin);

	EditorNode *editor;
	PhysicalBone3D *selected = nullptr;
	PhysicalBone3DEditor physical_bone_editor;

public:
	virtual String get_name() const override { return "PhysicalBone3D"; }
	virtual bool handles(Object *p_object) const override { return p_object->is_class("PhysicalBone3D"); }
	virtual void make_visible(bool p_visible) override;
	virtual void edit(Object *p_node) override;

	PhysicalBone3DEditorPlugin(EditorNode *p_editor);
};

#endif
