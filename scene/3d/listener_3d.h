
/*  listener_3d.h                                                        */



#ifndef LISTENER_3D_H
#define LISTENER_3D_H

#include "scene/3d/node_3d.h"
#include "scene/main/window.h"

class Listener3D : public Node3D {
	GDCLASS(Listener3D, Node3D);

private:
	bool force_change;
	bool current;

	RID scenario_id;

	virtual bool _can_gizmo_scale() const;
	virtual RES _get_gizmo_geometry() const;

	friend class Viewport;
	void _update_audio_listener_state();

protected:
	void _update_listener();
	virtual void _request_listener_update();

	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;
	void _notification(int p_what);

	static void _bind_methods();

public:
	void make_current();
	void clear_current();
	bool is_current() const;

	virtual Transform get_listener_transform() const;

	void set_visible_layers(uint32_t p_layers);
	uint32_t get_visible_layers() const;

	Listener3D();
	~Listener3D();
};

#endif
