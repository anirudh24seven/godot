
/*  popup.h                                                              */

#ifndef POPUP_H
#define POPUP_H

#include "scene/main/window.h"

#include "core/local_vector.h"

class Popup : public Window {
	GDCLASS(Popup, Window);

	LocalVector<Window *> visible_parents;
	bool popped_up = false;

	void _input_from_window(const Ref<InputEvent> &p_event);

	void _initialize_visible_parents();
	void _deinitialize_visible_parents();

	void _parent_focused();

protected:
	void _close_pressed();
	virtual Rect2i _popup_adjust_rect() const override;

	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_as_minsize();
	Popup();
	~Popup();
};

class PopupPanel : public Popup {
	GDCLASS(PopupPanel, Popup);

	Panel *panel;

protected:
	void _update_child_rects();
	void _notification(int p_what);

	virtual Size2 _get_contents_minimum_size() const override;

public:
	void set_child_rect(Control *p_child);
	PopupPanel();
};

#endif
