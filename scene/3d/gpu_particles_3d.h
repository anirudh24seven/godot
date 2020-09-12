
/*  gpu_particles_3d.h                                                   */

#ifndef PARTICLES_H
#define PARTICLES_H

#include "core/rid.h"
#include "scene/3d/visual_instance_3d.h"
#include "scene/resources/material.h"

class GPUParticles3D : public GeometryInstance3D {
private:
	GDCLASS(GPUParticles3D, GeometryInstance3D);

public:
	enum DrawOrder {
		DRAW_ORDER_INDEX,
		DRAW_ORDER_LIFETIME,
		DRAW_ORDER_VIEW_DEPTH,
	};

	enum {
		MAX_DRAW_PASSES = 4
	};

private:
	RID particles;

	bool one_shot;
	int amount;
	float lifetime;
	float pre_process_time;
	float explosiveness_ratio;
	float randomness_ratio;
	float speed_scale;
	AABB visibility_aabb;
	bool local_coords;
	int fixed_fps;
	bool fractional_delta;

	Ref<Material> process_material;

	DrawOrder draw_order;

	Vector<Ref<Mesh>> draw_passes;

protected:
	static void _bind_methods();
	void _notification(int p_what);
	virtual void _validate_property(PropertyInfo &property) const override;

public:
	AABB get_aabb() const override;
	Vector<Face3> get_faces(uint32_t p_usage_flags) const override;

	void set_emitting(bool p_emitting);
	void set_amount(int p_amount);
	void set_lifetime(float p_lifetime);
	void set_one_shot(bool p_one_shot);
	void set_pre_process_time(float p_time);
	void set_explosiveness_ratio(float p_ratio);
	void set_randomness_ratio(float p_ratio);
	void set_visibility_aabb(const AABB &p_aabb);
	void set_use_local_coordinates(bool p_enable);
	void set_process_material(const Ref<Material> &p_material);
	void set_speed_scale(float p_scale);

	bool is_emitting() const;
	int get_amount() const;
	float get_lifetime() const;
	bool get_one_shot() const;
	float get_pre_process_time() const;
	float get_explosiveness_ratio() const;
	float get_randomness_ratio() const;
	AABB get_visibility_aabb() const;
	bool get_use_local_coordinates() const;
	Ref<Material> get_process_material() const;
	float get_speed_scale() const;

	void set_fixed_fps(int p_count);
	int get_fixed_fps() const;

	void set_fractional_delta(bool p_enable);
	bool get_fractional_delta() const;

	void set_draw_order(DrawOrder p_order);
	DrawOrder get_draw_order() const;

	void set_draw_passes(int p_count);
	int get_draw_passes() const;

	void set_draw_pass_mesh(int p_pass, const Ref<Mesh> &p_mesh);
	Ref<Mesh> get_draw_pass_mesh(int p_pass) const;

	virtual String get_configuration_warning() const override;

	void restart();

	AABB capture_aabb() const;
	GPUParticles3D();
	~GPUParticles3D();
};

VARIANT_ENUM_CAST(GPUParticles3D::DrawOrder)

#endif // PARTICLES_H
