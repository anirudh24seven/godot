
/*  gpu_particles_3d_editor_plugin.h                                     */



#ifndef PARTICLES_EDITOR_PLUGIN_H
#define PARTICLES_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/3d/gpu_particles_3d.h"
#include "scene/gui/spin_box.h"

class GPUParticles3DEditorBase : public Control {
	GDCLASS(GPUParticles3DEditorBase, Control);

protected:
	Node3D *base_node;
	Panel *panel;
	MenuButton *options;
	HBoxContainer *particles_editor_hb;

	SceneTreeDialog *emission_tree_dialog;

	ConfirmationDialog *emission_dialog;
	SpinBox *emission_amount;
	OptionButton *emission_fill;

	Vector<Face3> geometry;

	bool _generate(Vector<Vector3> &points, Vector<Vector3> &normals);
	virtual void _generate_emission_points() = 0;
	void _node_selected(const NodePath &p_path);

	static void _bind_methods();

public:
	GPUParticles3DEditorBase();
};

class GPUParticles3DEditor : public GPUParticles3DEditorBase {
	GDCLASS(GPUParticles3DEditor, GPUParticles3DEditorBase);

	ConfirmationDialog *generate_aabb;
	SpinBox *generate_seconds;
	GPUParticles3D *node;

	enum Menu {

		MENU_OPTION_GENERATE_AABB,
		MENU_OPTION_CREATE_EMISSION_VOLUME_FROM_NODE,
		MENU_OPTION_CLEAR_EMISSION_VOLUME,
		MENU_OPTION_CONVERT_TO_CPU_PARTICLES,
		MENU_OPTION_RESTART,

	};

	void _generate_aabb();

	void _menu_option(int);

	friend class GPUParticles3DEditorPlugin;

	virtual void _generate_emission_points() override;

protected:
	void _notification(int p_notification);
	void _node_removed(Node *p_node);
	static void _bind_methods();

public:
	void edit(GPUParticles3D *p_particles);
	GPUParticles3DEditor();
};

class GPUParticles3DEditorPlugin : public EditorPlugin {
	GDCLASS(GPUParticles3DEditorPlugin, EditorPlugin);

	GPUParticles3DEditor *particles_editor;
	EditorNode *editor;

public:
	virtual String get_name() const override { return "GPUParticles3D"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	GPUParticles3DEditorPlugin(EditorNode *p_node);
	~GPUParticles3DEditorPlugin();
};

#endif // PARTICLES_EDITOR_PLUGIN_H
