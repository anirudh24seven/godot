
/*  bone_attachment_3d.cpp                                               */



#include "bone_attachment_3d.h"

void BoneAttachment3D::_validate_property(PropertyInfo &property) const {
	if (property.name == "bone_name") {
		Skeleton3D *parent = Object::cast_to<Skeleton3D>(get_parent());

		if (parent) {
			String names;
			for (int i = 0; i < parent->get_bone_count(); i++) {
				if (i > 0) {
					names += ",";
				}
				names += parent->get_bone_name(i);
			}

			property.hint = PROPERTY_HINT_ENUM;
			property.hint_string = names;
		} else {
			property.hint = PROPERTY_HINT_NONE;
			property.hint_string = "";
		}
	}
}

void BoneAttachment3D::_check_bind() {
	Skeleton3D *sk = Object::cast_to<Skeleton3D>(get_parent());
	if (sk) {
		int idx = sk->find_bone(bone_name);
		if (idx != -1) {
			sk->bind_child_node_to_bone(idx, this);
			set_transform(sk->get_bone_global_pose(idx));
			bound = true;
		}
	}
}

void BoneAttachment3D::_check_unbind() {
	if (bound) {
		Skeleton3D *sk = Object::cast_to<Skeleton3D>(get_parent());
		if (sk) {
			int idx = sk->find_bone(bone_name);
			if (idx != -1) {
				sk->unbind_child_node_from_bone(idx, this);
			}
		}
		bound = false;
	}
}

void BoneAttachment3D::set_bone_name(const String &p_name) {
	if (is_inside_tree()) {
		_check_unbind();
	}

	bone_name = p_name;

	if (is_inside_tree()) {
		_check_bind();
	}
}

String BoneAttachment3D::get_bone_name() const {
	return bone_name;
}

void BoneAttachment3D::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			_check_bind();
		} break;
		case NOTIFICATION_EXIT_TREE: {
			_check_unbind();
		} break;
	}
}

BoneAttachment3D::BoneAttachment3D() {
	bound = false;
}

void BoneAttachment3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_bone_name", "bone_name"), &BoneAttachment3D::set_bone_name);
	ClassDB::bind_method(D_METHOD("get_bone_name"), &BoneAttachment3D::get_bone_name);

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "bone_name"), "set_bone_name", "get_bone_name");
}
