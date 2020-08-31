
/*  editor_import_plugin.h                                               */



#ifndef EDITOR_IMPORT_PLUGIN_H
#define EDITOR_IMPORT_PLUGIN_H

#include "core/io/resource_importer.h"

class EditorImportPlugin : public ResourceImporter {
	GDCLASS(EditorImportPlugin, ResourceImporter);

protected:
	static void _bind_methods();

public:
	EditorImportPlugin();
	virtual String get_importer_name() const override;
	virtual String get_visible_name() const override;
	virtual void get_recognized_extensions(List<String> *p_extensions) const override;
	virtual String get_preset_name(int p_idx) const override;
	virtual int get_preset_count() const override;
	virtual String get_save_extension() const override;
	virtual String get_resource_type() const override;
	virtual float get_priority() const override;
	virtual int get_import_order() const override;
	virtual void get_import_options(List<ImportOption> *r_options, int p_preset) const override;
	virtual bool get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const override;
	virtual Error import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files, Variant *r_metadata = nullptr) override;
};

#endif //EDITOR_IMPORT_PLUGIN_H
