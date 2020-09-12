
/*  subviewport_container.h                                              */

#ifndef VIEWPORTCONTAINER_H
#define VIEWPORTCONTAINER_H

#include "scene/gui/container.h"

class SubViewportContainer : public Container {
	GDCLASS(SubViewportContainer, Container);

	bool stretch;
	int shrink;

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_stretch(bool p_enable);
	bool is_stretch_enabled() const;

	void _input(const Ref<InputEvent> &p_event);
	void _unhandled_input(const Ref<InputEvent> &p_event);
	void set_stretch_shrink(int p_shrink);
	int get_stretch_shrink() const;

	virtual Size2 get_minimum_size() const override;

	SubViewportContainer();
};

#endif // VIEWPORTCONTAINER_H
