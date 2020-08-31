
/*  texture_editor_plugin.h                                              */



#ifndef TEXTURE_EDITOR_PLUGIN_H
#define TEXTURE_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/resources/texture.h"

class TextureEditor : public Control {
	GDCLASS(TextureEditor, Control);

	Ref<Texture2D> texture;

protected:
	void _notification(int p_what);
	void _gui_input(Ref<InputEvent> p_event);
	void _changed_callback(Object *p_changed, const char *p_prop) override;
	static void _bind_methods();

public:
	void edit(Ref<Texture2D> p_texture);
	TextureEditor();
	~TextureEditor();
};

class EditorInspectorPluginTexture : public EditorInspectorPlugin {
	GDCLASS(EditorInspectorPluginTexture, EditorInspectorPlugin);

public:
	virtual bool can_handle(Object *p_object) override;
	virtual void parse_begin(Object *p_object) override;
};

class TextureEditorPlugin : public EditorPlugin {
	GDCLASS(TextureEditorPlugin, EditorPlugin);

public:
	virtual String get_name() const override { return "Texture2D"; }

	TextureEditorPlugin(EditorNode *p_node);
};

#endif // TEXTURE_EDITOR_PLUGIN_H
