
/*  gdscript_cache.h                                                     */



#ifndef GDSCRIPT_CACHE_H
#define GDSCRIPT_CACHE_H

#include "core/hash_map.h"
#include "core/os/mutex.h"
#include "core/reference.h"
#include "core/set.h"
#include "gdscript.h"

class GDScriptAnalyzer;
class GDScriptParser;

class GDScriptParserRef : public Reference {
public:
	enum Status {
		EMPTY,
		PARSED,
		INHERITANCE_SOLVED,
		INTERFACE_SOLVED,
		FULLY_SOLVED,
	};

private:
	GDScriptParser *parser = nullptr;
	GDScriptAnalyzer *analyzer = nullptr;
	Status status = EMPTY;
	String path;

	friend class GDScriptCache;

public:
	bool is_valid() const;
	Status get_status() const;
	GDScriptParser *get_parser() const;
	Error raise_status(Status p_new_status);

	GDScriptParserRef() {}
	~GDScriptParserRef();
};

class GDScriptCache {
	// String key is full path.
	HashMap<String, GDScriptParserRef *> parser_map;
	HashMap<String, GDScript *> shallow_gdscript_cache;
	HashMap<String, GDScript *> full_gdscript_cache;
	HashMap<String, Set<String>> dependencies;

	friend class GDScript;
	friend class GDScriptParserRef;

	static GDScriptCache *singleton;

	Mutex lock;
	static void remove_script(const String &p_path);

public:
	static Ref<GDScriptParserRef> get_parser(const String &p_path, GDScriptParserRef::Status status, Error &r_error, const String &p_owner = String());
	static String get_source_code(const String &p_path);
	static Ref<GDScript> get_shallow_script(const String &p_path, const String &p_owner = String());
	static Ref<GDScript> get_full_script(const String &p_path, Error &r_error, const String &p_owner = String());
	static Error finish_compiling(const String &p_owner);

	GDScriptCache();
	~GDScriptCache();
};

#endif // GDSCRIPT_CACHE_H
