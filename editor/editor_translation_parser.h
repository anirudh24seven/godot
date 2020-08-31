
/*  editor_translation_parser.h                                          */



#ifndef EDITOR_TRANSLATION_PARSER_H
#define EDITOR_TRANSLATION_PARSER_H

#include "core/error_list.h"
#include "core/reference.h"

class EditorTranslationParserPlugin : public Reference {
	GDCLASS(EditorTranslationParserPlugin, Reference);

protected:
	static void _bind_methods();

public:
	virtual Error parse_file(const String &p_path, Vector<String> *r_ids, Vector<Vector<String>> *r_ids_ctx_plural);
	virtual void get_recognized_extensions(List<String> *r_extensions) const;
};

class EditorTranslationParser {
	static EditorTranslationParser *singleton;

public:
	enum ParserType {
		STANDARD, // GDScript, CSharp, ...
		CUSTOM // User-defined parser plugins. This will override standard parsers if the same extension type is defined.
	};

	static EditorTranslationParser *get_singleton();

	Vector<Ref<EditorTranslationParserPlugin>> standard_parsers;
	Vector<Ref<EditorTranslationParserPlugin>> custom_parsers;

	void get_recognized_extensions(List<String> *r_extensions) const;
	bool can_parse(const String &p_extension) const;
	Ref<EditorTranslationParserPlugin> get_parser(const String &p_extension) const;
	void add_parser(const Ref<EditorTranslationParserPlugin> &p_parser, ParserType p_type);
	void remove_parser(const Ref<EditorTranslationParserPlugin> &p_parser, ParserType p_type);
	void clean_parsers();

	EditorTranslationParser();
	~EditorTranslationParser();
};

#endif // EDITOR_TRANSLATION_PARSER_H
