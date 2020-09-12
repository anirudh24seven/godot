
/*  node_2d.h                                                            */

#ifndef NODE2D_H
#define NODE2D_H

#include "scene/main/canvas_item.h"

class Node2D : public CanvasItem {
	GDCLASS(Node2D, CanvasItem);

	Point2 pos;
	float angle;
	Size2 _scale;
	float skew;
	int z_index;
	bool z_relative;

	Transform2D _mat;

	bool _xform_dirty;

	void _update_transform();

	void _update_xform_values();

protected:
	static void _bind_methods();

public:
#ifdef TOOLS_ENABLED
	virtual Dictionary _edit_get_state() const override;
	virtual void _edit_set_state(const Dictionary &p_state) override;

	virtual void _edit_set_position(const Point2 &p_position) override;
	virtual Point2 _edit_get_position() const override;

	virtual void _edit_set_scale(const Size2 &p_scale) override;
	virtual Size2 _edit_get_scale() const override;

	virtual void _edit_set_rotation(float p_rotation) override;
	virtual float _edit_get_rotation() const override;
	virtual bool _edit_use_rotation() const override;

	virtual void _edit_set_rect(const Rect2 &p_edit_rect) override;
#endif

	void set_position(const Point2 &p_pos);
	void set_rotation(float p_radians);
	void set_rotation_degrees(float p_degrees);
	void set_skew(float p_radians);
	void set_skew_degrees(float p_radians);
	void set_scale(const Size2 &p_scale);

	void rotate(float p_radians);
	void move_x(float p_delta, bool p_scaled = false);
	void move_y(float p_delta, bool p_scaled = false);
	void translate(const Vector2 &p_amount);
	void global_translate(const Vector2 &p_amount);
	void apply_scale(const Size2 &p_amount);

	Point2 get_position() const;
	float get_rotation() const;
	float get_skew() const;
	float get_rotation_degrees() const;
	float get_skew_degrees() const;
	Size2 get_scale() const;

	Point2 get_global_position() const;
	float get_global_rotation() const;
	float get_global_rotation_degrees() const;
	Size2 get_global_scale() const;

	void set_transform(const Transform2D &p_transform);
	void set_global_transform(const Transform2D &p_transform);
	void set_global_position(const Point2 &p_pos);
	void set_global_rotation(float p_radians);
	void set_global_rotation_degrees(float p_degrees);
	void set_global_scale(const Size2 &p_scale);

	void set_z_index(int p_z);
	int get_z_index() const;

	void look_at(const Vector2 &p_pos);
	float get_angle_to(const Vector2 &p_pos) const;

	Point2 to_local(Point2 p_global) const;
	Point2 to_global(Point2 p_local) const;

	void set_z_as_relative(bool p_enabled);
	bool is_z_relative() const;

	Transform2D get_relative_transform_to_parent(const Node *p_parent) const;

	Transform2D get_transform() const override;

	Node2D();
};

#endif // NODE2D_H
