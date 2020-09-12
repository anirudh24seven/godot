
/*  check_box.h                                                          */

#ifndef CHECK_BOX_H
#define CHECK_BOX_H

#include "scene/gui/button.h"
/**
@author Mariano Suligoy <marianognu.esyrpg@gmail.com>
*/
class CheckBox : public Button {
	GDCLASS(CheckBox, Button);

protected:
	Size2 get_icon_size() const;
	Size2 get_minimum_size() const override;
	void _notification(int p_what);

	bool is_radio();

public:
	CheckBox(const String &p_text = String());
	~CheckBox();
};

#endif
