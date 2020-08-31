
/*  listener_3d.cpp                                                      */



#include "listener_3d.h"

#include "scene/resources/mesh.h"

void Listener3D::_update_audio_listener_state() {
}

void Listener3D::_request_listener_update() {
	_update_listener();
}

bool Listener3D::_set(const StringName &p_name, const Variant &p_value) {
	if (p_name == "current") {
		if (p_value.operator bool()) {
			make_current();
		} else {
			clear_current();
		}
	} else {
		return false;
	}

	return true;
}

bool Listener3D::_get(const StringName &p_name, Variant &r_ret) const {
	if (p_name == "current") {
		if (is_inside_tree() && get_tree()->is_node_being_edited(this)) {
			r_ret = current;
		} else {
			r_ret = is_current();
		}
	} else {
		return false;
	}

	return true;
}

void Listener3D::_get_property_list(List<PropertyInfo> *p_list) const {
	p_list->push_back(PropertyInfo(Variant::BOOL, "current"));
}

void Listener3D::_update_listener() {
	if (is_inside_tree() && is_current()) {
		get_viewport()->_listener_transform_changed_notify();
	}
}

void Listener3D::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_WORLD: {
			bool first_listener = get_viewport()->_listener_add(this);
			if (!get_tree()->is_node_being_edited(this) && (current || first_listener)) {
				make_current();
			}
		} break;
		case NOTIFICATION_TRANSFORM_CHANGED: {
			_request_listener_update();
		} break;
		case NOTIFICATION_EXIT_WORLD: {
			if (!get_tree()->is_node_being_edited(this)) {
				if (is_current()) {
					clear_current();
					current = true; //keep it true

				} else {
					current = false;
				}
			}

			get_viewport()->_listener_remove(this);

		} break;
	}
}

Transform Listener3D::get_listener_transform() const {
	return get_global_transform().orthonormalized();
}

void Listener3D::make_current() {
	current = true;

	if (!is_inside_tree()) {
		return;
	}

	get_viewport()->_listener_set(this);
}

void Listener3D::clear_current() {
	current = false;
	if (!is_inside_tree()) {
		return;
	}

	if (get_viewport()->get_listener() == this) {
		get_viewport()->_listener_set(nullptr);
		get_viewport()->_listener_make_next_current(this);
	}
}

bool Listener3D::is_current() const {
	if (is_inside_tree() && !get_tree()->is_node_being_edited(this)) {
		return get_viewport()->get_listener() == this;
	} else {
		return current;
	}

	return false;
}

bool Listener3D::_can_gizmo_scale() const {
	return false;
}

RES Listener3D::_get_gizmo_geometry() const {
	Ref<ArrayMesh> mesh = memnew(ArrayMesh);

	return mesh;
}

void Listener3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("make_current"), &Listener3D::make_current);
	ClassDB::bind_method(D_METHOD("clear_current"), &Listener3D::clear_current);
	ClassDB::bind_method(D_METHOD("is_current"), &Listener3D::is_current);
	ClassDB::bind_method(D_METHOD("get_listener_transform"), &Listener3D::get_listener_transform);
}

Listener3D::Listener3D() {
	current = false;
	force_change = false;
	set_notify_transform(true);
	//active=false;
}

Listener3D::~Listener3D() {
}
