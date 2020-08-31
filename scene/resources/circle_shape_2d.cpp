
/*  circle_shape_2d.cpp                                                  */



#include "circle_shape_2d.h"

#include "servers/physics_server_2d.h"
#include "servers/rendering_server.h"

bool CircleShape2D::_edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const {
	return p_point.length() < get_radius() + p_tolerance;
}

void CircleShape2D::_update_shape() {
	PhysicsServer2D::get_singleton()->shape_set_data(get_rid(), radius);
	emit_changed();
}

void CircleShape2D::set_radius(real_t p_radius) {
	radius = p_radius;
	_update_shape();
}

real_t CircleShape2D::get_radius() const {
	return radius;
}

void CircleShape2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_radius", "radius"), &CircleShape2D::set_radius);
	ClassDB::bind_method(D_METHOD("get_radius"), &CircleShape2D::get_radius);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius", PROPERTY_HINT_RANGE, "0.01,16384,0.5"), "set_radius", "get_radius");
}

Rect2 CircleShape2D::get_rect() const {
	Rect2 rect;
	rect.position = -Point2(get_radius(), get_radius());
	rect.size = Point2(get_radius(), get_radius()) * 2.0;
	return rect;
}

real_t CircleShape2D::get_enclosing_radius() const {
	return radius;
}

void CircleShape2D::draw(const RID &p_to_rid, const Color &p_color) {
	Vector<Vector2> points;
	for (int i = 0; i < 24; i++) {
		points.push_back(Vector2(Math::cos(i * Math_PI * 2 / 24.0), Math::sin(i * Math_PI * 2 / 24.0)) * get_radius());
	}

	Vector<Color> col;
	col.push_back(p_color);
	RenderingServer::get_singleton()->canvas_item_add_polygon(p_to_rid, points, col);
}

CircleShape2D::CircleShape2D() :
		Shape2D(PhysicsServer2D::get_singleton()->circle_shape_create()) {
	radius = 10;
	_update_shape();
}
