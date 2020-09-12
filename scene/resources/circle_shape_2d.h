
/*  circle_shape_2d.h                                                    */

#ifndef CIRCLE_SHAPE_2D_H
#define CIRCLE_SHAPE_2D_H

#include "scene/resources/shape_2d.h"

class CircleShape2D : public Shape2D {
	GDCLASS(CircleShape2D, Shape2D);

	real_t radius;
	void _update_shape();

protected:
	static void _bind_methods();

public:
	virtual bool _edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const override;

	void set_radius(real_t p_radius);
	real_t get_radius() const;

	virtual void draw(const RID &p_to_rid, const Color &p_color) override;
	virtual Rect2 get_rect() const override;
	virtual real_t get_enclosing_radius() const override;

	CircleShape2D();
};

#endif // CIRCLE_SHAPE_2D_H
