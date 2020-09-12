
/*  shader_types.h                                                       */

#ifndef SHADERTYPES_H
#define SHADERTYPES_H

#include "core/ordered_hash_map.h"
#include "servers/rendering_server.h"
#include "shader_language.h"

class ShaderTypes {
	struct Type {
		Map<StringName, ShaderLanguage::FunctionInfo> functions;
		Vector<StringName> modes;
	};

	Map<RS::ShaderMode, Type> shader_modes;

	static ShaderTypes *singleton;

	Set<String> shader_types;

public:
	static ShaderTypes *get_singleton() { return singleton; }

	const Map<StringName, ShaderLanguage::FunctionInfo> &get_functions(RS::ShaderMode p_mode);
	const Vector<StringName> &get_modes(RS::ShaderMode p_mode);
	const Set<String> &get_types();

	ShaderTypes();
};

#endif // SHADERTYPES_H
