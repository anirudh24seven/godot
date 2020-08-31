
/*  physical_bone_3d_editor_plugin.cpp                                   */



#include "physical_bone_3d_editor_plugin.h"

#include "editor/plugins/node_3d_editor_plugin.h"
#include "scene/3d/physics_body_3d.h"

void PhysicalBone3DEditor::_bind_methods() {
}

void PhysicalBone3DEditor::_on_toggle_button_transform_joint(bool p_is_pressed) {
	_set_move_joint();
}

void PhysicalBone3DEditor::_set_move_joint() {
	if (selected) {
		selected->_set_gizmo_move_joint(button_transform_joint->is_pressed());
	}
}

PhysicalBone3DEditor::PhysicalBone3DEditor(EditorNode *p_editor) :
		editor(p_editor) {
	spatial_editor_hb = memnew(HBoxContainer);
	spatial_editor_hb->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	spatial_editor_hb->set_alignment(BoxContainer::ALIGN_BEGIN);
	Node3DEditor::get_singleton()->add_control_to_menu_panel(spatial_editor_hb);

	spatial_editor_hb->add_child(memnew(VSeparator));

	button_transform_joint = memnew(Button);
	button_transform_joint->set_flat(true);
	spatial_editor_hb->add_child(button_transform_joint);

	button_transform_joint->set_text(TTR("Move Joint"));
	button_transform_joint->set_icon(Node3DEditor::get_singleton()->get_theme_icon("PhysicalBone3D", "EditorIcons"));
	button_transform_joint->set_toggle_mode(true);
	button_transform_joint->connect("toggled", callable_mp(this, &PhysicalBone3DEditor::_on_toggle_button_transform_joint));

	hide();
}

void PhysicalBone3DEditor::set_selected(PhysicalBone3D *p_pb) {
	button_transform_joint->set_pressed(false);

	_set_move_joint();
	selected = p_pb;
	_set_move_joint();
}

void PhysicalBone3DEditor::hide() {
	spatial_editor_hb->hide();
}

void PhysicalBone3DEditor::show() {
	spatial_editor_hb->show();
}

PhysicalBone3DEditorPlugin::PhysicalBone3DEditorPlugin(EditorNode *p_editor) :
		editor(p_editor),
		physical_bone_editor(editor) {}

void PhysicalBone3DEditorPlugin::make_visible(bool p_visible) {
	if (p_visible) {
		physical_bone_editor.show();
	} else {
		physical_bone_editor.hide();
		physical_bone_editor.set_selected(nullptr);
		selected = nullptr;
	}
}

void PhysicalBone3DEditorPlugin::edit(Object *p_node) {
	selected = static_cast<PhysicalBone3D *>(p_node); // Trust it
	ERR_FAIL_COND(!selected);

	physical_bone_editor.set_selected(selected);
}
