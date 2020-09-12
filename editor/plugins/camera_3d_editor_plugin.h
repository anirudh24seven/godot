
/*  camera_3d_editor_plugin.h                                            */

#ifndef CAMERA_EDITOR_PLUGIN_H
#define CAMERA_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/3d/camera_3d.h"

class Camera3DEditor : public Control {
	GDCLASS(Camera3DEditor, Control);

	Panel *panel;
	Button *preview;
	Node *node;

	void _pressed();

protected:
	void _node_removed(Node *p_node);
	static void _bind_methods();

public:
	void edit(Node *p_camera);
	Camera3DEditor();
};

class Camera3DEditorPlugin : public EditorPlugin {
	GDCLASS(Camera3DEditorPlugin, EditorPlugin);

	//CameraEditor *camera_editor;
	EditorNode *editor;

public:
	virtual String get_name() const override { return "Camera3D"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	Camera3DEditorPlugin(EditorNode *p_node);
	~Camera3DEditorPlugin();
};

#endif // CAMERA_EDITOR_PLUGIN_H
