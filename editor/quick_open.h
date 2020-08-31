
/*  quick_open.h                                                         */



#ifndef EDITOR_QUICK_OPEN_H
#define EDITOR_QUICK_OPEN_H

#include "core/oa_hash_map.h"
#include "editor_file_system.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/tree.h"

class EditorQuickOpen : public ConfirmationDialog {
	GDCLASS(EditorQuickOpen, ConfirmationDialog);

	LineEdit *search_box;
	Tree *search_options;
	StringName base_type;
	bool allow_multi_select;

	Vector<String> files;
	OAHashMap<String, Ref<Texture2D>> icons;

	struct Entry {
		String path;
		float score;
	};

	struct EntryComparator {
		_FORCE_INLINE_ bool operator()(const Entry &A, const Entry &B) const {
			return A.score > B.score;
		}
	};

	void _update_search();
	void _build_search_cache(EditorFileSystemDirectory *p_efsd);
	float _score_path(const String &p_search, const String &p_path);

	void _confirmed();
	virtual void cancel_pressed() override;
	void _cleanup();

	void _sbox_input(const Ref<InputEvent> &p_ie);
	void _text_changed(const String &p_newtext);

	void _theme_changed();

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	StringName get_base_type() const;

	String get_selected() const;
	Vector<String> get_selected_files() const;

	void popup_dialog(const StringName &p_base, bool p_enable_multi = false, bool p_dontclear = false);
	EditorQuickOpen();
};

#endif // EDITOR_QUICK_OPEN_H
