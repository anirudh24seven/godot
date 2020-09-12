
/*  register_types.cpp                                                   */

#include "register_types.h"

#include "core/engine.h"

#include "csharp_script.h"

CSharpLanguage *script_language_cs = nullptr;
Ref<ResourceFormatLoaderCSharpScript> resource_loader_cs;
Ref<ResourceFormatSaverCSharpScript> resource_saver_cs;

_GodotSharp *_godotsharp = nullptr;

void register_mono_types() {
	ClassDB::register_class<CSharpScript>();

	_godotsharp = memnew(_GodotSharp);

	ClassDB::register_class<_GodotSharp>();
	Engine::get_singleton()->add_singleton(Engine::Singleton("GodotSharp", _GodotSharp::get_singleton()));

	script_language_cs = memnew(CSharpLanguage);
	script_language_cs->set_language_index(ScriptServer::get_language_count());
	ScriptServer::register_language(script_language_cs);

	resource_loader_cs.instance();
	ResourceLoader::add_resource_format_loader(resource_loader_cs);

	resource_saver_cs.instance();
	ResourceSaver::add_resource_format_saver(resource_saver_cs);
}

void unregister_mono_types() {
	ScriptServer::unregister_language(script_language_cs);

	if (script_language_cs) {
		memdelete(script_language_cs);
	}

	ResourceLoader::remove_resource_format_loader(resource_loader_cs);
	resource_loader_cs.unref();

	ResourceSaver::remove_resource_format_saver(resource_saver_cs);
	resource_saver_cs.unref();

	if (_godotsharp) {
		memdelete(_godotsharp);
	}
}
