
/*  mesh_editor_plugin.h                                                 */

#ifndef MESH_EDITOR_PLUGIN_H
#define MESH_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/3d/camera_3d.h"
#include "scene/3d/light_3d.h"
#include "scene/3d/mesh_instance_3d.h"
#include "scene/gui/subviewport_container.h"
#include "scene/resources/material.h"

class MeshEditor : public SubViewportContainer {
	GDCLASS(MeshEditor, SubViewportContainer);

	float rot_x;
	float rot_y;

	SubViewport *viewport;
	MeshInstance3D *mesh_instance;
	Node3D *rotation;
	DirectionalLight3D *light1;
	DirectionalLight3D *light2;
	Camera3D *camera;

	Ref<Mesh> mesh;

	TextureButton *light_1_switch;
	TextureButton *light_2_switch;

	void _button_pressed(Node *p_button);
	bool first_enter;

	void _update_rotation();

protected:
	void _notification(int p_what);
	void _gui_input(Ref<InputEvent> p_event);
	static void _bind_methods();

public:
	void edit(Ref<Mesh> p_mesh);
	MeshEditor();
};

class EditorInspectorPluginMesh : public EditorInspectorPlugin {
	GDCLASS(EditorInspectorPluginMesh, EditorInspectorPlugin);

public:
	virtual bool can_handle(Object *p_object) override;
	virtual void parse_begin(Object *p_object) override;
};

class MeshEditorPlugin : public EditorPlugin {
	GDCLASS(MeshEditorPlugin, EditorPlugin);

public:
	virtual String get_name() const override { return "Mesh"; }

	MeshEditorPlugin(EditorNode *p_node);
};

#endif
