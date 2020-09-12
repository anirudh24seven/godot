
/*  pot_generator.h                                                      */

#ifndef POT_GENERATOR_H
#define POT_GENERATOR_H

#include "core/ordered_hash_map.h"
#include "core/os/file_access.h"
#include "core/set.h"

//#define DEBUG_POT

class POTGenerator {
	static POTGenerator *singleton;

	struct MsgidData {
		String ctx;
		String plural;
		Set<String> locations;
	};
	// Store msgid as key and the additional data around the msgid - if it's under a context, has plurals and its file locations.
	OrderedHashMap<String, Vector<MsgidData>> all_translation_strings;

	void _write_to_pot(const String &p_file);
	void _write_msgid(FileAccess *r_file, const String &p_id, bool p_plural);
	void _add_new_msgid(const String &p_msgid, const String &p_context, const String &p_plural, const String &p_location);

#ifdef DEBUG_POT
	void _print_all_translation_strings();
#endif

public:
	static POTGenerator *get_singleton();
	void generate_pot(const String &p_file);

	POTGenerator();
	~POTGenerator();
};

#endif // POT_GENERATOR_H
