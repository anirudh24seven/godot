
/*  baked_lightmap_editor_plugin.h                                       */

#ifndef BAKED_LIGHTMAP_EDITOR_PLUGIN_H
#define BAKED_LIGHTMAP_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/3d/baked_lightmap.h"
#include "scene/resources/material.h"

class BakedLightmapEditorPlugin : public EditorPlugin {
	GDCLASS(BakedLightmapEditorPlugin, EditorPlugin);

	BakedLightmap *lightmap;

	Button *bake;
	EditorNode *editor;

	EditorFileDialog *file_dialog;
	static EditorProgress *tmp_progress;
	static bool bake_func_step(float p_progress, const String &p_description, void *, bool p_refresh);
	static void bake_func_end();

	void _bake_select_file(const String &p_file);
	void _bake();

protected:
	static void _bind_methods();

public:
	virtual String get_name() const override { return "BakedLightmap"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	BakedLightmapEditorPlugin(EditorNode *p_node);
	~BakedLightmapEditorPlugin();
};

#endif
