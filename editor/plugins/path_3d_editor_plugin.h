
/*  path_3d_editor_plugin.h                                              */



#ifndef PATH_EDITOR_PLUGIN_H
#define PATH_EDITOR_PLUGIN_H

#include "editor/node_3d_editor_gizmos.h"
#include "scene/3d/path_3d.h"

class Path3DGizmo : public EditorNode3DGizmo {
	GDCLASS(Path3DGizmo, EditorNode3DGizmo);

	Path3D *path;
	mutable Vector3 original;
	mutable float orig_in_length;
	mutable float orig_out_length;

public:
	virtual String get_handle_name(int p_idx) const override;
	virtual Variant get_handle_value(int p_idx) override;
	virtual void set_handle(int p_idx, Camera3D *p_camera, const Point2 &p_point) override;
	virtual void commit_handle(int p_idx, const Variant &p_restore, bool p_cancel = false) override;

	virtual void redraw() override;
	Path3DGizmo(Path3D *p_path = nullptr);
};

class Path3DGizmoPlugin : public EditorNode3DGizmoPlugin {
	GDCLASS(Path3DGizmoPlugin, EditorNode3DGizmoPlugin);

protected:
	Ref<EditorNode3DGizmo> create_gizmo(Node3D *p_spatial) override;

public:
	String get_name() const override;
	int get_priority() const override;
	Path3DGizmoPlugin();
};

class Path3DEditorPlugin : public EditorPlugin {
	GDCLASS(Path3DEditorPlugin, EditorPlugin);

	Separator *sep;
	Button *curve_create;
	Button *curve_edit;
	Button *curve_del;
	Button *curve_close;
	MenuButton *handle_menu;

	EditorNode *editor;

	Path3D *path;

	void _mode_changed(int p_idx);
	void _close_curve();
	void _handle_option_pressed(int p_option);
	bool handle_clicked;
	bool mirror_handle_angle;
	bool mirror_handle_length;

	enum HandleOption {
		HANDLE_OPTION_ANGLE,
		HANDLE_OPTION_LENGTH
	};

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	Path3D *get_edited_path() { return path; }

	static Path3DEditorPlugin *singleton;
	virtual bool forward_spatial_gui_input(Camera3D *p_camera, const Ref<InputEvent> &p_event) override;

	virtual String get_name() const override { return "Path3D"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	bool mirror_angle_enabled() { return mirror_handle_angle; }
	bool mirror_length_enabled() { return mirror_handle_length; }
	bool is_handle_clicked() { return handle_clicked; }
	void set_handle_clicked(bool clicked) { handle_clicked = clicked; }

	Path3DEditorPlugin(EditorNode *p_node);
	~Path3DEditorPlugin();
};

#endif // PATH_EDITOR_PLUGIN_H
