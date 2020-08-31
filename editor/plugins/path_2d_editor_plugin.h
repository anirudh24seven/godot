
/*  path_2d_editor_plugin.h                                              */



#ifndef PATH_2D_EDITOR_PLUGIN_H
#define PATH_2D_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/2d/path_2d.h"

class CanvasItemEditor;

class Path2DEditor : public HBoxContainer {
	GDCLASS(Path2DEditor, HBoxContainer);

	UndoRedo *undo_redo;

	CanvasItemEditor *canvas_item_editor;
	EditorNode *editor;
	Panel *panel;
	Path2D *node;

	HBoxContainer *base_hb;
	Separator *sep;

	enum Mode {
		MODE_CREATE,
		MODE_EDIT,
		MODE_EDIT_CURVE,
		MODE_DELETE,
		ACTION_CLOSE
	};

	Mode mode;
	Button *curve_create;
	Button *curve_edit;
	Button *curve_edit_curve;
	Button *curve_del;
	Button *curve_close;
	MenuButton *handle_menu;

	bool mirror_handle_angle;
	bool mirror_handle_length;
	bool on_edge;

	enum HandleOption {
		HANDLE_OPTION_ANGLE,
		HANDLE_OPTION_LENGTH
	};

	enum Action {

		ACTION_NONE,
		ACTION_MOVING_POINT,
		ACTION_MOVING_IN,
		ACTION_MOVING_OUT,
	};

	Action action;
	int action_point;
	Point2 moving_from;
	Point2 moving_screen_from;
	float orig_in_length;
	float orig_out_length;
	Vector2 edge_point;

	void _mode_selected(int p_mode);
	void _handle_option_pressed(int p_option);

	void _node_visibility_changed();
	friend class Path2DEditorPlugin;

protected:
	void _notification(int p_what);
	void _node_removed(Node *p_node);
	static void _bind_methods();

public:
	bool forward_gui_input(const Ref<InputEvent> &p_event);
	void forward_canvas_draw_over_viewport(Control *p_overlay);
	void edit(Node *p_path2d);
	Path2DEditor(EditorNode *p_editor);
};

class Path2DEditorPlugin : public EditorPlugin {
	GDCLASS(Path2DEditorPlugin, EditorPlugin);

	Path2DEditor *path2d_editor;
	EditorNode *editor;

public:
	virtual bool forward_canvas_gui_input(const Ref<InputEvent> &p_event) override { return path2d_editor->forward_gui_input(p_event); }
	virtual void forward_canvas_draw_over_viewport(Control *p_overlay) override { path2d_editor->forward_canvas_draw_over_viewport(p_overlay); }

	virtual String get_name() const override { return "Path2D"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	Path2DEditorPlugin(EditorNode *p_node);
	~Path2DEditorPlugin();
};

#endif // PATH_2D_EDITOR_PLUGIN_H
