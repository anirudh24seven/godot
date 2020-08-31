
/*  resource_importer_bitmask.h                                          */



#ifndef RESOURCE_IMPORTER_BITMASK_H
#define RESOURCE_IMPORTER_BITMASK_H

#include "core/image.h"
#include "core/io/resource_importer.h"

class StreamBitMap;

class ResourceImporterBitMap : public ResourceImporter {
	GDCLASS(ResourceImporterBitMap, ResourceImporter);

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

	ResourceImporterBitMap();
	~ResourceImporterBitMap();
};
#endif // RESOURCE_IMPORTER_BITMASK_H
