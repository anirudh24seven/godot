
/*  reflection_probe.h                                                   */

#ifndef REFLECTIONPROBE_H
#define REFLECTIONPROBE_H

#include "scene/3d/visual_instance_3d.h"
#include "scene/resources/sky.h"
#include "scene/resources/texture.h"
#include "servers/rendering_server.h"

class ReflectionProbe : public VisualInstance3D {
	GDCLASS(ReflectionProbe, VisualInstance3D);

public:
	enum UpdateMode {
		UPDATE_ONCE,
		UPDATE_ALWAYS,
	};

	enum AmbientMode {
		AMBIENT_DISABLED,
		AMBIENT_ENVIRONMENT,
		AMBIENT_COLOR
	};

private:
	RID probe;
	float intensity;
	float max_distance;
	Vector3 extents;
	Vector3 origin_offset;
	bool box_projection;
	bool enable_shadows;
	bool interior;
	AmbientMode ambient_mode;
	Color ambient_color;
	float ambient_color_energy;

	uint32_t cull_mask;
	UpdateMode update_mode;

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const override;

public:
	void set_intensity(float p_intensity);
	float get_intensity() const;

	void set_ambient_mode(AmbientMode p_mode);
	AmbientMode get_ambient_mode() const;

	void set_ambient_color(Color p_ambient);
	Color get_ambient_color() const;

	void set_ambient_color_energy(float p_energy);
	float get_ambient_color_energy() const;

	void set_interior_ambient_probe_contribution(float p_contribution);
	float get_interior_ambient_probe_contribution() const;

	void set_max_distance(float p_distance);
	float get_max_distance() const;

	void set_extents(const Vector3 &p_extents);
	Vector3 get_extents() const;

	void set_origin_offset(const Vector3 &p_extents);
	Vector3 get_origin_offset() const;

	void set_as_interior(bool p_enable);
	bool is_set_as_interior() const;

	void set_enable_box_projection(bool p_enable);
	bool is_box_projection_enabled() const;

	void set_enable_shadows(bool p_enable);
	bool are_shadows_enabled() const;

	void set_cull_mask(uint32_t p_layers);
	uint32_t get_cull_mask() const;

	void set_update_mode(UpdateMode p_mode);
	UpdateMode get_update_mode() const;

	virtual AABB get_aabb() const override;
	virtual Vector<Face3> get_faces(uint32_t p_usage_flags) const override;

	ReflectionProbe();
	~ReflectionProbe();
};

VARIANT_ENUM_CAST(ReflectionProbe::AmbientMode);
VARIANT_ENUM_CAST(ReflectionProbe::UpdateMode);

#endif // REFLECTIONPROBE_H
