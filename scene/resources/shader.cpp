
/*  shader.cpp                                                           */

#include "shader.h"
#include "core/os/file_access.h"
#include "scene/scene_string_names.h"
#include "servers/rendering/shader_language.h"
#include "servers/rendering_server.h"
#include "texture.h"

Shader::Mode Shader::get_mode() const {
	return mode;
}

void Shader::set_code(const String &p_code) {
	String type = ShaderLanguage::get_shader_type(p_code);

	if (type == "canvas_item") {
		mode = MODE_CANVAS_ITEM;
	} else if (type == "particles") {
		mode = MODE_PARTICLES;
	} else if (type == "sky") {
		mode = MODE_SKY;
	} else {
		mode = MODE_SPATIAL;
	}

	RenderingServer::get_singleton()->shader_set_code(shader, p_code);
	params_cache_dirty = true;

	emit_changed();
}

String Shader::get_code() const {
	_update_shader();
	return RenderingServer::get_singleton()->shader_get_code(shader);
}

void Shader::get_param_list(List<PropertyInfo> *p_params) const {
	_update_shader();

	List<PropertyInfo> local;
	RenderingServer::get_singleton()->shader_get_param_list(shader, &local);
	params_cache.clear();
	params_cache_dirty = false;

	for (List<PropertyInfo>::Element *E = local.front(); E; E = E->next()) {
		PropertyInfo pi = E->get();
		if (default_textures.has(pi.name)) { //do not show default textures
			continue;
		}
		pi.name = "shader_param/" + pi.name;
		params_cache[pi.name] = E->get().name;
		if (p_params) {
			//small little hack
			if (pi.type == Variant::_RID) {
				pi.type = Variant::OBJECT;
			}
			p_params->push_back(pi);
		}
	}
}

RID Shader::get_rid() const {
	_update_shader();

	return shader;
}

void Shader::set_default_texture_param(const StringName &p_param, const Ref<Texture2D> &p_texture) {
	if (p_texture.is_valid()) {
		default_textures[p_param] = p_texture;
		RS::get_singleton()->shader_set_default_texture_param(shader, p_param, p_texture->get_rid());
	} else {
		default_textures.erase(p_param);
		RS::get_singleton()->shader_set_default_texture_param(shader, p_param, RID());
	}

	emit_changed();
}

Ref<Texture2D> Shader::get_default_texture_param(const StringName &p_param) const {
	if (default_textures.has(p_param)) {
		return default_textures[p_param];
	} else {
		return Ref<Texture2D>();
	}
}

void Shader::get_default_texture_param_list(List<StringName> *r_textures) const {
	for (const Map<StringName, Ref<Texture2D>>::Element *E = default_textures.front(); E; E = E->next()) {
		r_textures->push_back(E->key());
	}
}

bool Shader::is_text_shader() const {
	return true;
}

bool Shader::has_param(const StringName &p_param) const {
	return params_cache.has("shader_param/" + p_param);
}

void Shader::_update_shader() const {
}

void Shader::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_mode"), &Shader::get_mode);

	ClassDB::bind_method(D_METHOD("set_code", "code"), &Shader::set_code);
	ClassDB::bind_method(D_METHOD("get_code"), &Shader::get_code);

	ClassDB::bind_method(D_METHOD("set_default_texture_param", "param", "texture"), &Shader::set_default_texture_param);
	ClassDB::bind_method(D_METHOD("get_default_texture_param", "param"), &Shader::get_default_texture_param);

	ClassDB::bind_method(D_METHOD("has_param", "name"), &Shader::has_param);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "code", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_code", "get_code");

	BIND_ENUM_CONSTANT(MODE_SPATIAL);
	BIND_ENUM_CONSTANT(MODE_CANVAS_ITEM);
	BIND_ENUM_CONSTANT(MODE_PARTICLES);
	BIND_ENUM_CONSTANT(MODE_SKY);
}

Shader::Shader() {
	mode = MODE_SPATIAL;
	shader = RenderingServer::get_singleton()->shader_create();
	params_cache_dirty = true;
}

Shader::~Shader() {
	RenderingServer::get_singleton()->free(shader);
}

////////////

RES ResourceFormatLoaderShader::load(const String &p_path, const String &p_original_path, Error *r_error, bool p_use_sub_threads, float *r_progress, bool p_no_cache) {
	if (r_error) {
		*r_error = ERR_FILE_CANT_OPEN;
	}

	Ref<Shader> shader;
	shader.instance();

	Vector<uint8_t> buffer = FileAccess::get_file_as_array(p_path);

	String str;
	str.parse_utf8((const char *)buffer.ptr(), buffer.size());

	shader->set_code(str);

	if (r_error) {
		*r_error = OK;
	}

	return shader;
}

void ResourceFormatLoaderShader::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("shader");
}

bool ResourceFormatLoaderShader::handles_type(const String &p_type) const {
	return (p_type == "Shader");
}

String ResourceFormatLoaderShader::get_resource_type(const String &p_path) const {
	String el = p_path.get_extension().to_lower();
	if (el == "shader") {
		return "Shader";
	}
	return "";
}

Error ResourceFormatSaverShader::save(const String &p_path, const RES &p_resource, uint32_t p_flags) {
	Ref<Shader> shader = p_resource;
	ERR_FAIL_COND_V(shader.is_null(), ERR_INVALID_PARAMETER);

	String source = shader->get_code();

	Error err;
	FileAccess *file = FileAccess::open(p_path, FileAccess::WRITE, &err);

	ERR_FAIL_COND_V_MSG(err, err, "Cannot save shader '" + p_path + "'.");

	file->store_string(source);
	if (file->get_error() != OK && file->get_error() != ERR_FILE_EOF) {
		memdelete(file);
		return ERR_CANT_CREATE;
	}
	file->close();
	memdelete(file);

	return OK;
}

void ResourceFormatSaverShader::get_recognized_extensions(const RES &p_resource, List<String> *p_extensions) const {
	if (const Shader *shader = Object::cast_to<Shader>(*p_resource)) {
		if (shader->is_text_shader()) {
			p_extensions->push_back("shader");
		}
	}
}

bool ResourceFormatSaverShader::recognize(const RES &p_resource) const {
	return p_resource->get_class_name() == "Shader"; //only shader, not inherited
}
