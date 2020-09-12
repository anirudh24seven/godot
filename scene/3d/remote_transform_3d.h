
/*  remote_transform_3d.h                                                */

#ifndef REMOTETRANSFORM_H
#define REMOTETRANSFORM_H

#include "scene/3d/node_3d.h"

class RemoteTransform3D : public Node3D {
	GDCLASS(RemoteTransform3D, Node3D);

	NodePath remote_node;

	ObjectID cache;

	bool use_global_coordinates;
	bool update_remote_position;
	bool update_remote_rotation;
	bool update_remote_scale;

	void _update_remote();
	void _update_cache();

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	void set_remote_node(const NodePath &p_remote_node);
	NodePath get_remote_node() const;

	void set_use_global_coordinates(const bool p_enable);
	bool get_use_global_coordinates() const;

	void set_update_position(const bool p_update);
	bool get_update_position() const;

	void set_update_rotation(const bool p_update);
	bool get_update_rotation() const;

	void set_update_scale(const bool p_update);
	bool get_update_scale() const;

	void force_update_cache();

	virtual String get_configuration_warning() const override;

	RemoteTransform3D();
};

#endif // REMOTETRANSFORM_H
