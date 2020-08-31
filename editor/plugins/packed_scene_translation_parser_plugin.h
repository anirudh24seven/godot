
/*  packed_scene_translation_parser_plugin.h                             */



#ifndef PACKED_SCENE_TRANSLATION_PARSER_PLUGIN_H
#define PACKED_SCENE_TRANSLATION_PARSER_PLUGIN_H

#include "editor/editor_translation_parser.h"

class PackedSceneEditorTranslationParserPlugin : public EditorTranslationParserPlugin {
	GDCLASS(PackedSceneEditorTranslationParserPlugin, EditorTranslationParserPlugin);

	// Scene Node's properties that contain translation strings.
	Set<String> lookup_properties;

public:
	virtual Error parse_file(const String &p_path, Vector<String> *r_ids, Vector<Vector<String>> *r_ids_ctx_plural) override;
	virtual void get_recognized_extensions(List<String> *r_extensions) const override;

	PackedSceneEditorTranslationParserPlugin();
};

#endif // PACKED_SCENE_TRANSLATION_PARSER_PLUGIN_H
