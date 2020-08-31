
/*  gpu_particles_2d_editor_plugin.h                                     */



#ifndef PARTICLES_2D_EDITOR_PLUGIN_H
#define PARTICLES_2D_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/2d/collision_polygon_2d.h"
#include "scene/2d/gpu_particles_2d.h"
#include "scene/gui/box_container.h"
#include "scene/gui/file_dialog.h"

class GPUParticles2DEditorPlugin : public EditorPlugin {
	GDCLASS(GPUParticles2DEditorPlugin, EditorPlugin);

	enum {

		MENU_GENERATE_VISIBILITY_RECT,
		MENU_LOAD_EMISSION_MASK,
		MENU_CLEAR_EMISSION_MASK,
		MENU_OPTION_CONVERT_TO_CPU_PARTICLES,
		MENU_RESTART
	};

	enum EmissionMode {
		EMISSION_MODE_SOLID,
		EMISSION_MODE_BORDER,
		EMISSION_MODE_BORDER_DIRECTED
	};

	GPUParticles2D *particles;

	EditorFileDialog *file;
	EditorNode *editor;

	HBoxContainer *toolbar;
	MenuButton *menu;

	SpinBox *epoints;

	ConfirmationDialog *generate_visibility_rect;
	SpinBox *generate_seconds;

	ConfirmationDialog *emission_mask;
	OptionButton *emission_mask_mode;
	CheckBox *emission_colors;

	String source_emission_file;

	UndoRedo *undo_redo;
	void _file_selected(const String &p_file);
	void _menu_callback(int p_idx);
	void _generate_visibility_rect();
	void _generate_emission_mask();

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	virtual String get_name() const override { return "GPUParticles2D"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	GPUParticles2DEditorPlugin(EditorNode *p_node);
	~GPUParticles2DEditorPlugin();
};

#endif // PARTICLES_2D_EDITOR_PLUGIN_H
