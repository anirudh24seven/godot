
/*  csg_gizmos.h                                                         */



#ifndef CSG_GIZMOS_H
#define CSG_GIZMOS_H

#include "csg_shape.h"
#include "editor/editor_plugin.h"
#include "editor/node_3d_editor_gizmos.h"

class CSGShape3DGizmoPlugin : public EditorNode3DGizmoPlugin {
	GDCLASS(CSGShape3DGizmoPlugin, EditorNode3DGizmoPlugin);

public:
	bool has_gizmo(Node3D *p_spatial) override;
	String get_name() const override;
	int get_priority() const override;
	bool is_selectable_when_hidden() const override;
	void redraw(EditorNode3DGizmo *p_gizmo) override;

	String get_handle_name(const EditorNode3DGizmo *p_gizmo, int p_idx) const override;
	Variant get_handle_value(EditorNode3DGizmo *p_gizmo, int p_idx) const override;
	void set_handle(EditorNode3DGizmo *p_gizmo, int p_idx, Camera3D *p_camera, const Point2 &p_point) override;
	void commit_handle(EditorNode3DGizmo *p_gizmo, int p_idx, const Variant &p_restore, bool p_cancel) override;

	CSGShape3DGizmoPlugin();
};

class EditorPluginCSG : public EditorPlugin {
	GDCLASS(EditorPluginCSG, EditorPlugin);

public:
	EditorPluginCSG(EditorNode *p_editor);
};

#endif // CSG_GIZMOS_H
