
/*  popup.h                                                              */



#ifndef POPUP_H
#define POPUP_H

#include "scene/main/window.h"

class Popup : public Window {
	GDCLASS(Popup, Window);

	Window *parent_visible;

	void _input_from_window(const Ref<InputEvent> &p_event);
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
