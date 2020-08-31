
/*  gdscript_highlighter.h                                               */



#ifndef GDSCRIPT_HIGHLIGHTER_H
#define GDSCRIPT_HIGHLIGHTER_H

#include "editor/plugins/script_editor_plugin.h"
#include "scene/gui/text_edit.h"

class GDScriptSyntaxHighlighter : public EditorSyntaxHighlighter {
	GDCLASS(GDScriptSyntaxHighlighter, EditorSyntaxHighlighter)

private:
	struct ColorRegion {
		Color color;
		String start_key;
		String end_key;
		bool line_only;
	};
	Vector<ColorRegion> color_regions;
	Map<int, int> color_region_cache;

	Dictionary keywords;
	Dictionary member_keywords;

	enum Type {
		NONE,
		REGION,
		NODE_PATH,
		SYMBOL,
		NUMBER,
		FUNCTION,
		KEYWORD,
		MEMBER,
		IDENTIFIER,
		TYPE,
	};

	// colours
	Color font_color;
	Color symbol_color;
	Color function_color;
	Color function_definition_color;
	Color built_in_type_color;
	Color number_color;
	Color member_color;
	Color node_path_color;
	Color type_color;

	void add_color_region(const String &p_start_key, const String &p_end_key, const Color &p_color, bool p_line_only = false);

public:
	virtual void _update_cache() override;
	virtual Dictionary _get_line_syntax_highlighting(int p_line) override;

	virtual String _get_name() const override;
	virtual Array _get_supported_languages() const override;

	virtual Ref<EditorSyntaxHighlighter> _create() const override;
};

#endif // GDSCRIPT_HIGHLIGHTER_H
