
/*  multimesh_instance_3d.cpp                                            */



#include "multimesh_instance_3d.h"

void MultiMeshInstance3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_multimesh", "multimesh"), &MultiMeshInstance3D::set_multimesh);
	ClassDB::bind_method(D_METHOD("get_multimesh"), &MultiMeshInstance3D::get_multimesh);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "multimesh", PROPERTY_HINT_RESOURCE_TYPE, "MultiMesh"), "set_multimesh", "get_multimesh");
}

void MultiMeshInstance3D::set_multimesh(const Ref<MultiMesh> &p_multimesh) {
	multimesh = p_multimesh;
	if (multimesh.is_valid()) {
		set_base(multimesh->get_rid());
	} else {
		set_base(RID());
	}
}

Ref<MultiMesh> MultiMeshInstance3D::get_multimesh() const {
	return multimesh;
}

Vector<Face3> MultiMeshInstance3D::get_faces(uint32_t p_usage_flags) const {
	return Vector<Face3>();
}

AABB MultiMeshInstance3D::get_aabb() const {
	if (multimesh.is_null()) {
		return AABB();
	} else {
		return multimesh->get_aabb();
	}
}

MultiMeshInstance3D::MultiMeshInstance3D() {
}

MultiMeshInstance3D::~MultiMeshInstance3D() {
}
