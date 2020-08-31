
/*  editor_path.h                                                        */



#ifndef EDITOR_PATH_H
#define EDITOR_PATH_H

#include "editor_data.h"
#include "scene/gui/menu_button.h"

class EditorPath : public MenuButton {
	GDCLASS(EditorPath, MenuButton);

	EditorHistory *history;

	Vector<ObjectID> objects;
	EditorPath();

	void _id_pressed(int p_idx);
	void _about_to_show();
	void _add_children_to_popup(Object *p_obj, int p_depth = 0);

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void update_path();

	EditorPath(EditorHistory *p_history);
};

#endif // EDITOR_PATH_H
