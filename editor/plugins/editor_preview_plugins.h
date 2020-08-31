
/*  editor_preview_plugins.h                                             */



#ifndef EDITORPREVIEWPLUGINS_H
#define EDITORPREVIEWPLUGINS_H

#include "editor/editor_resource_preview.h"

void post_process_preview(Ref<Image> p_image);

class EditorTexturePreviewPlugin : public EditorResourcePreviewGenerator {
	GDCLASS(EditorTexturePreviewPlugin, EditorResourcePreviewGenerator);

public:
	virtual bool handles(const String &p_type) const override;
	virtual bool generate_small_preview_automatically() const override;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const override;

	EditorTexturePreviewPlugin();
};

class EditorImagePreviewPlugin : public EditorResourcePreviewGenerator {
	GDCLASS(EditorImagePreviewPlugin, EditorResourcePreviewGenerator);

public:
	virtual bool handles(const String &p_type) const override;
	virtual bool generate_small_preview_automatically() const override;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const override;

	EditorImagePreviewPlugin();
};

class EditorBitmapPreviewPlugin : public EditorResourcePreviewGenerator {
	GDCLASS(EditorBitmapPreviewPlugin, EditorResourcePreviewGenerator);

public:
	virtual bool handles(const String &p_type) const override;
	virtual bool generate_small_preview_automatically() const override;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const override;

	EditorBitmapPreviewPlugin();
};

class EditorPackedScenePreviewPlugin : public EditorResourcePreviewGenerator {
public:
	virtual bool handles(const String &p_type) const;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const;
	virtual Ref<Texture2D> generate_from_path(const String &p_path, const Size2 &p_size) const;

	EditorPackedScenePreviewPlugin();
};

class EditorMaterialPreviewPlugin : public EditorResourcePreviewGenerator {
	GDCLASS(EditorMaterialPreviewPlugin, EditorResourcePreviewGenerator);

	RID scenario;
	RID sphere;
	RID sphere_instance;
	RID viewport;
	RID viewport_texture;
	RID light;
	RID light_instance;
	RID light2;
	RID light_instance2;
	RID camera;
	mutable volatile bool preview_done;

	void _preview_done(const Variant &p_udata);

protected:
	static void _bind_methods();

public:
	virtual bool handles(const String &p_type) const override;
	virtual bool generate_small_preview_automatically() const override;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const override;

	EditorMaterialPreviewPlugin();
	~EditorMaterialPreviewPlugin();
};

class EditorScriptPreviewPlugin : public EditorResourcePreviewGenerator {
public:
	virtual bool handles(const String &p_type) const;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const;

	EditorScriptPreviewPlugin();
};

class EditorAudioStreamPreviewPlugin : public EditorResourcePreviewGenerator {
public:
	virtual bool handles(const String &p_type) const;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const;

	EditorAudioStreamPreviewPlugin();
};

class EditorMeshPreviewPlugin : public EditorResourcePreviewGenerator {
	GDCLASS(EditorMeshPreviewPlugin, EditorResourcePreviewGenerator);

	RID scenario;
	RID mesh_instance;
	RID viewport;
	RID viewport_texture;
	RID light;
	RID light_instance;
	RID light2;
	RID light_instance2;
	RID camera;
	mutable volatile bool preview_done;

	void _preview_done(const Variant &p_udata);

protected:
	static void _bind_methods();

public:
	virtual bool handles(const String &p_type) const override;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const override;

	EditorMeshPreviewPlugin();
	~EditorMeshPreviewPlugin();
};

class EditorFontPreviewPlugin : public EditorResourcePreviewGenerator {
	GDCLASS(EditorFontPreviewPlugin, EditorResourcePreviewGenerator);

	RID viewport;
	RID viewport_texture;
	RID canvas;
	RID canvas_item;
	mutable volatile bool preview_done;

	void _preview_done(const Variant &p_udata);

protected:
	static void _bind_methods();

public:
	virtual bool handles(const String &p_type) const override;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const override;
	virtual Ref<Texture2D> generate_from_path(const String &p_path, const Size2 &p_size) const override;

	EditorFontPreviewPlugin();
	~EditorFontPreviewPlugin();
};
#endif // EDITORPREVIEWPLUGINS_H
