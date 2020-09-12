
/*  panel.h                                                              */

#ifndef PANEL_H
#define PANEL_H

#include "scene/gui/control.h"

class Panel : public Control {
	GDCLASS(Panel, Control);

public:
	enum Mode {
		MODE_BACKGROUND,
		MODE_FOREGROUND,
	};

private:
	Mode mode = MODE_BACKGROUND;

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_mode(Mode p_mode);
	Mode get_mode() const;

	Panel();
	~Panel();
};

VARIANT_ENUM_CAST(Panel::Mode)

#endif // PANEL_H
