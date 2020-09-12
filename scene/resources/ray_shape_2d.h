
/*  ray_shape_2d.h                                                       */

#ifndef RAY_SHAPE_2D_H
#define RAY_SHAPE_2D_H

#include "scene/resources/shape_2d.h"

class RayShape2D : public Shape2D {
	GDCLASS(RayShape2D, Shape2D);

	real_t length;
	bool slips_on_slope;

	void _update_shape();

protected:
	static void _bind_methods();

public:
	void set_length(real_t p_length);
	real_t get_length() const;

	void set_slips_on_slope(bool p_active);
	bool get_slips_on_slope() const;

	virtual void draw(const RID &p_to_rid, const Color &p_color) override;
	virtual Rect2 get_rect() const override;
	virtual real_t get_enclosing_radius() const override;

	RayShape2D();
};

#endif // RAY_SHAPE_2D_H
