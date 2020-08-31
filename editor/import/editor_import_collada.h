
/*  editor_import_collada.h                                              */



#ifndef EDITOR_IMPORT_COLLADA_H
#define EDITOR_IMPORT_COLLADA_H

#include "editor/import/resource_importer_scene.h"

class EditorSceneImporterCollada : public EditorSceneImporter {
	GDCLASS(EditorSceneImporterCollada, EditorSceneImporter);

public:
	virtual uint32_t get_import_flags() const override;
	virtual void get_extensions(List<String> *r_extensions) const override;
	virtual Node *import_scene(const String &p_path, uint32_t p_flags, int p_bake_fps, List<String> *r_missing_deps = nullptr, Error *r_err = nullptr) override;
	virtual Ref<Animation> import_animation(const String &p_path, uint32_t p_flags, int p_bake_fps) override;

	EditorSceneImporterCollada();
};

#endif
