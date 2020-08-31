
/*  baked_lightmap_editor_plugin.cpp                                     */



#include "baked_lightmap_editor_plugin.h"

void BakedLightmapEditorPlugin::_bake_select_file(const String &p_file) {
	if (lightmap) {
		BakedLightmap::BakeError err;
		if (get_tree()->get_edited_scene_root() && get_tree()->get_edited_scene_root() == lightmap) {
			err = lightmap->bake(lightmap, p_file, bake_func_step);
		} else {
			err = lightmap->bake(lightmap->get_parent(), p_file, bake_func_step);
		}

		bake_func_end();

		switch (err) {
			case BakedLightmap::BAKE_ERROR_NO_SAVE_PATH: {
				String scene_path = lightmap->get_filename();
				if (scene_path == String()) {
					scene_path = lightmap->get_owner()->get_filename();
				}
				if (scene_path == String()) {
					EditorNode::get_singleton()->show_warning(TTR("Can't determine a save path for lightmap images.\nSave your scene and try again."));
					break;
				}
				scene_path = scene_path.get_basename() + ".lmbake";

				file_dialog->set_current_path(scene_path);
				file_dialog->popup_file_dialog();

			} break;
			case BakedLightmap::BAKE_ERROR_NO_MESHES:
				EditorNode::get_singleton()->show_warning(TTR("No meshes to bake. Make sure they contain an UV2 channel and that the 'Bake Light' flag is on."));
				break;
			case BakedLightmap::BAKE_ERROR_CANT_CREATE_IMAGE:
				EditorNode::get_singleton()->show_warning(TTR("Failed creating lightmap images, make sure path is writable."));
				break;
			default: {
			}
		}
	}
}

void BakedLightmapEditorPlugin::_bake() {
	_bake_select_file("");
}

void BakedLightmapEditorPlugin::edit(Object *p_object) {
	BakedLightmap *s = Object::cast_to<BakedLightmap>(p_object);
	if (!s) {
		return;
	}

	lightmap = s;
}

bool BakedLightmapEditorPlugin::handles(Object *p_object) const {
	return p_object->is_class("BakedLightmap");
}

void BakedLightmapEditorPlugin::make_visible(bool p_visible) {
	if (p_visible) {
		bake->show();
	} else {
		bake->hide();
	}
}

EditorProgress *BakedLightmapEditorPlugin::tmp_progress = nullptr;

bool BakedLightmapEditorPlugin::bake_func_step(float p_progress, const String &p_description, void *, bool p_refresh) {
	if (!tmp_progress) {
		tmp_progress = memnew(EditorProgress("bake_lightmaps", TTR("Bake Lightmaps"), 1000, false));
		ERR_FAIL_COND_V(tmp_progress == nullptr, false);
	}
	return tmp_progress->step(p_description, p_progress * 1000, p_refresh);
}

void BakedLightmapEditorPlugin::bake_func_end() {
	if (tmp_progress != nullptr) {
		memdelete(tmp_progress);
		tmp_progress = nullptr;
	}
}

void BakedLightmapEditorPlugin::_bind_methods() {
	ClassDB::bind_method("_bake", &BakedLightmapEditorPlugin::_bake);
}

BakedLightmapEditorPlugin::BakedLightmapEditorPlugin(EditorNode *p_node) {
	editor = p_node;
	bake = memnew(Button);
	bake->set_flat(true);
	bake->set_icon(editor->get_gui_base()->get_theme_icon("Bake", "EditorIcons"));
	bake->set_text(TTR("Bake Lightmaps"));
	bake->hide();
	bake->connect("pressed", Callable(this, "_bake"));
	add_control_to_container(CONTAINER_SPATIAL_EDITOR_MENU, bake);
	lightmap = nullptr;

	file_dialog = memnew(EditorFileDialog);
	file_dialog->set_file_mode(EditorFileDialog::FILE_MODE_SAVE_FILE);
	file_dialog->add_filter("*.lmbake ; LightMap Bake");
	file_dialog->set_title(TTR("Select lightmap bake file:"));
	file_dialog->connect("file_selected", callable_mp(this, &BakedLightmapEditorPlugin::_bake_select_file));
	bake->add_child(file_dialog);
}

BakedLightmapEditorPlugin::~BakedLightmapEditorPlugin() {
}
