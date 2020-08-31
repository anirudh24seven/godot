
/*  camera_effects.h                                                     */



#ifndef CAMERA_EFFECTS_H
#define CAMERA_EFFECTS_H

#include "core/resource.h"
#include "core/rid.h"

class CameraEffects : public Resource {
	GDCLASS(CameraEffects, Resource);

private:
	RID camera_effects;

	// DOF blur
	bool dof_blur_far_enabled = false;
	float dof_blur_far_distance = 10;
	float dof_blur_far_transition = 5;

	bool dof_blur_near_enabled = false;
	float dof_blur_near_distance = 2;
	float dof_blur_near_transition = 1;

	float dof_blur_amount = 0.1;
	void _update_dof_blur();

	// Override exposure
	bool override_exposure_enabled = false;
	float override_exposure = 1.0;
	void _update_override_exposure();

protected:
	static void _bind_methods();

public:
	virtual RID get_rid() const override;

	// DOF blur
	void set_dof_blur_far_enabled(bool p_enabled);
	bool is_dof_blur_far_enabled() const;
	void set_dof_blur_far_distance(float p_distance);
	float get_dof_blur_far_distance() const;
	void set_dof_blur_far_transition(float p_distance);
	float get_dof_blur_far_transition() const;

	void set_dof_blur_near_enabled(bool p_enabled);
	bool is_dof_blur_near_enabled() const;
	void set_dof_blur_near_distance(float p_distance);
	float get_dof_blur_near_distance() const;
	void set_dof_blur_near_transition(float p_distance);
	float get_dof_blur_near_transition() const;

	void set_dof_blur_amount(float p_amount);
	float get_dof_blur_amount() const;

	// Override exposure
	void set_override_exposure_enabled(bool p_enabled);
	bool is_override_exposure_enabled() const;
	void set_override_exposure(float p_exposure);
	float get_override_exposure() const;

	CameraEffects();
	~CameraEffects();
};

#endif // CAMERA_EFFECTS_H
