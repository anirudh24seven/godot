
/*  pluginscript_loader.h                                                */

#ifndef PYTHONSCRIPT_PY_LOADER_H
#define PYTHONSCRIPT_PY_LOADER_H

// Godot imports
#include "core/io/resource_loader.h"
#include "core/io/resource_saver.h"
#include "core/script_language.h"

class PluginScriptLanguage;

class ResourceFormatLoaderPluginScript : public ResourceFormatLoader {
	PluginScriptLanguage *_language;

public:
	ResourceFormatLoaderPluginScript(PluginScriptLanguage *language);
	virtual RES load(const String &p_path, const String &p_original_path = "", Error *r_error = nullptr, bool p_use_sub_threads = false, float *r_progress = nullptr, bool p_no_cache = false);
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual bool handles_type(const String &p_type) const;
	virtual String get_resource_type(const String &p_path) const;
};

class ResourceFormatSaverPluginScript : public ResourceFormatSaver {
	PluginScriptLanguage *_language;

public:
	ResourceFormatSaverPluginScript(PluginScriptLanguage *language);
	virtual Error save(const String &p_path, const RES &p_resource, uint32_t p_flags = 0);
	virtual void get_recognized_extensions(const RES &p_resource, List<String> *p_extensions) const;
	virtual bool recognize(const RES &p_resource) const;
};

#endif // PYTHONSCRIPT_PY_LOADER_H
