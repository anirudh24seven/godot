
/*  cpu_particles_3d_editor_plugin.cpp                                   */



#include "cpu_particles_3d_editor_plugin.h"

#include "editor/plugins/node_3d_editor_plugin.h"

void CPUParticles3DEditor::_node_removed(Node *p_node) {
	if (p_node == node) {
		node = nullptr;
		hide();
	}
}

void CPUParticles3DEditor::_notification(int p_notification) {
	if (p_notification == NOTIFICATION_ENTER_TREE) {
		options->set_icon(get_theme_icon("CPUParticles3D", "EditorIcons"));
	}
}

void CPUParticles3DEditor::_menu_option(int p_option) {
	switch (p_option) {
		case MENU_OPTION_CREATE_EMISSION_VOLUME_FROM_NODE: {
			emission_tree_dialog->popup_scenetree_dialog();

		} break;

		case MENU_OPTION_RESTART: {
			node->restart();

		} break;
	}
}

void CPUParticles3DEditor::edit(CPUParticles3D *p_particles) {
	base_node = p_particles;
	node = p_particles;
}

void CPUParticles3DEditor::_generate_emission_points() {
	/// hacer codigo aca
	Vector<Vector3> points;
	Vector<Vector3> normals;

	if (!_generate(points, normals)) {
		return;
	}

	if (normals.size() == 0) {
		node->set_emission_shape(CPUParticles3D::EMISSION_SHAPE_POINTS);
		node->set_emission_points(points);
	} else {
		node->set_emission_shape(CPUParticles3D::EMISSION_SHAPE_DIRECTED_POINTS);
		node->set_emission_points(points);
		node->set_emission_normals(normals);
	}
}

void CPUParticles3DEditor::_bind_methods() {
}

CPUParticles3DEditor::CPUParticles3DEditor() {
	particles_editor_hb = memnew(HBoxContainer);
	Node3DEditor::get_singleton()->add_control_to_menu_panel(particles_editor_hb);
	options = memnew(MenuButton);
	options->set_switch_on_hover(true);
	particles_editor_hb->add_child(options);
	particles_editor_hb->hide();

	options->set_text(TTR("CPUParticles3D"));
	options->get_popup()->add_item(TTR("Restart"), MENU_OPTION_RESTART);
	options->get_popup()->add_item(TTR("Create Emission Points From Node"), MENU_OPTION_CREATE_EMISSION_VOLUME_FROM_NODE);
	options->get_popup()->connect("id_pressed", callable_mp(this, &CPUParticles3DEditor::_menu_option));
}

void CPUParticles3DEditorPlugin::edit(Object *p_object) {
	particles_editor->edit(Object::cast_to<CPUParticles3D>(p_object));
}

bool CPUParticles3DEditorPlugin::handles(Object *p_object) const {
	return p_object->is_class("CPUParticles3D");
}

void CPUParticles3DEditorPlugin::make_visible(bool p_visible) {
	if (p_visible) {
		particles_editor->show();
		particles_editor->particles_editor_hb->show();
	} else {
		particles_editor->particles_editor_hb->hide();
		particles_editor->hide();
		particles_editor->edit(nullptr);
	}
}

CPUParticles3DEditorPlugin::CPUParticles3DEditorPlugin(EditorNode *p_node) {
	editor = p_node;
	particles_editor = memnew(CPUParticles3DEditor);
	editor->get_viewport()->add_child(particles_editor);

	particles_editor->hide();
}

CPUParticles3DEditorPlugin::~CPUParticles3DEditorPlugin() {
}
