
/*  light_occluder_2d_editor_plugin.h                                    */

#ifndef LIGHT_OCCLUDER_2D_EDITOR_PLUGIN_H
#define LIGHT_OCCLUDER_2D_EDITOR_PLUGIN_H

#include "editor/plugins/abstract_polygon_2d_editor.h"
#include "scene/2d/light_occluder_2d.h"

class LightOccluder2DEditor : public AbstractPolygon2DEditor {
	GDCLASS(LightOccluder2DEditor, AbstractPolygon2DEditor);

	LightOccluder2D *node;

	Ref<OccluderPolygon2D> _ensure_occluder() const;

protected:
	virtual Node2D *_get_node() const override;
	virtual void _set_node(Node *p_polygon) override;

	virtual bool _is_line() const override;
	virtual int _get_polygon_count() const override;
	virtual Variant _get_polygon(int p_idx) const override;
	virtual void _set_polygon(int p_idx, const Variant &p_polygon) const override;

	virtual void _action_set_polygon(int p_idx, const Variant &p_previous, const Variant &p_polygon) override;

	virtual bool _has_resource() const override;
	virtual void _create_resource() override;

public:
	LightOccluder2DEditor(EditorNode *p_editor);
};

class LightOccluder2DEditorPlugin : public AbstractPolygon2DEditorPlugin {
	GDCLASS(LightOccluder2DEditorPlugin, AbstractPolygon2DEditorPlugin);

public:
	LightOccluder2DEditorPlugin(EditorNode *p_node);
};

#endif // LIGHT_OCCLUDER_2D_EDITOR_PLUGIN_H
