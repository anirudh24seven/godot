
/*  editor_asset_installer.h                                             */

#ifndef EDITORASSETINSTALLER_H
#define EDITORASSETINSTALLER_H

#include "scene/gui/dialogs.h"
#include "scene/gui/tree.h"
class EditorAssetInstaller : public ConfirmationDialog {
	GDCLASS(EditorAssetInstaller, ConfirmationDialog);

	Tree *tree;
	String package_path;
	AcceptDialog *error;
	Map<String, TreeItem *> status_map;
	bool updating;
	void _update_subitems(TreeItem *p_item, bool p_check, bool p_first = false);
	void _uncheck_parent(TreeItem *p_item);
	void _item_edited();
	virtual void ok_pressed() override;

protected:
	static void _bind_methods();

public:
	void open(const String &p_path, int p_depth = 0);
	EditorAssetInstaller();
};

#endif // EDITORASSETINSTALLER_H
