
/*  cpu_particles_3d_editor_plugin.h                                     */



#ifndef CPU_PARTICLES_EDITOR_PLUGIN_H
#define CPU_PARTICLES_EDITOR_PLUGIN_H

#include "editor/plugins/gpu_particles_3d_editor_plugin.h"
#include "scene/3d/cpu_particles_3d.h"

class CPUParticles3DEditor : public GPUParticles3DEditorBase {
	GDCLASS(CPUParticles3DEditor, GPUParticles3DEditorBase);

	enum Menu {

		MENU_OPTION_CREATE_EMISSION_VOLUME_FROM_NODE,
		MENU_OPTION_CLEAR_EMISSION_VOLUME,
		MENU_OPTION_RESTART

	};

	CPUParticles3D *node;

	void _menu_option(int);

	friend class CPUParticles3DEditorPlugin;

	virtual void _generate_emission_points() override;

protected:
	void _notification(int p_notification);
	void _node_removed(Node *p_node);
	static void _bind_methods();

public:
	void edit(CPUParticles3D *p_particles);
	CPUParticles3DEditor();
};

class CPUParticles3DEditorPlugin : public EditorPlugin {
	GDCLASS(CPUParticles3DEditorPlugin, EditorPlugin);

	CPUParticles3DEditor *particles_editor;
	EditorNode *editor;

public:
	virtual String get_name() const override { return "CPUParticles3D"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	CPUParticles3DEditorPlugin(EditorNode *p_node);
	~CPUParticles3DEditorPlugin();
};

#endif // CPU_PARTICLES_EDITOR_PLUGIN_H
