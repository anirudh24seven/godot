
/*  resource_importer_obj.h                                              */



#ifndef RESOURCEIMPORTEROBJ_H
#define RESOURCEIMPORTEROBJ_H

#include "resource_importer_scene.h"

class EditorOBJImporter : public EditorSceneImporter {
	GDCLASS(EditorOBJImporter, EditorSceneImporter);

public:
	virtual uint32_t get_import_flags() const override;
	virtual void get_extensions(List<String> *r_extensions) const override;
	virtual Node *import_scene(const String &p_path, uint32_t p_flags, int p_bake_fps, List<String> *r_missing_deps, Error *r_err = nullptr) override;
	virtual Ref<Animation> import_animation(const String &p_path, uint32_t p_flags, int p_bake_fps) override;

	EditorOBJImporter();
};

class ResourceImporterOBJ : public ResourceImporter {
	GDCLASS(ResourceImporterOBJ, ResourceImporter);

public:
	virtual String get_importer_name() const override;
	virtual String get_visible_name() const override;
	virtual void get_recognized_extensions(List<String> *p_extensions) const override;
	virtual String get_save_extension() const override;
	virtual String get_resource_type() const override;

	virtual int get_preset_count() const override;
	virtual String get_preset_name(int p_idx) const override;

	virtual void get_import_options(List<ImportOption> *r_options, int p_preset = 0) const override;
	virtual bool get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const override;

	virtual Error import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files = nullptr, Variant *r_metadata = nullptr) override;

	ResourceImporterOBJ();
};

#endif // RESOURCEIMPORTEROBJ_H
