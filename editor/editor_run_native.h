
/*  editor_run_native.h                                                  */



#ifndef EDITOR_RUN_NATIVE_H
#define EDITOR_RUN_NATIVE_H

#include "scene/gui/box_container.h"
#include "scene/gui/menu_button.h"

class EditorRunNative : public HBoxContainer {
	GDCLASS(EditorRunNative, HBoxContainer);

	Map<int, MenuButton *> menus;
	bool first;

	int resume_idx;
	int resume_platform;

	void _run_native(int p_idx, int p_platform);

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	bool is_deploy_debug_remote_enabled() const;

	void resume_run_native();

	EditorRunNative();
};

#endif // EDITOR_RUN_NATIVE_H
