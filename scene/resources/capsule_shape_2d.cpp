
/*  capsule_shape_2d.cpp                                                 */



#include "capsule_shape_2d.h"

#include "core/math/geometry_2d.h"
#include "servers/physics_server_2d.h"
#include "servers/rendering_server.h"

Vector<Vector2> CapsuleShape2D::_get_points() const {
	Vector<Vector2> points;
	for (int i = 0; i < 24; i++) {
		Vector2 ofs = Vector2(0, (i > 6 && i <= 18) ? -get_height() * 0.5 : get_height() * 0.5);

		points.push_back(Vector2(Math::sin(i * Math_PI * 2 / 24.0), Math::cos(i * Math_PI * 2 / 24.0)) * get_radius() + ofs);
		if (i == 6 || i == 18) {
			points.push_back(Vector2(Math::sin(i * Math_PI * 2 / 24.0), Math::cos(i * Math_PI * 2 / 24.0)) * get_radius() - ofs);
		}
	}

	return points;
}

bool CapsuleShape2D::_edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const {
	return Geometry2D::is_point_in_polygon(p_point, _get_points());
}

void CapsuleShape2D::_update_shape() {
	PhysicsServer2D::get_singleton()->shape_set_data(get_rid(), Vector2(radius, height));
	emit_changed();
}

void CapsuleShape2D::set_radius(real_t p_radius) {
	radius = p_radius;
	_update_shape();
}

real_t CapsuleShape2D::get_radius() const {
	return radius;
}

void CapsuleShape2D::set_height(real_t p_height) {
	height = p_height;
	if (height < 0) {
		height = 0;
	}

	_update_shape();
}

real_t CapsuleShape2D::get_height() const {
	return height;
}

void CapsuleShape2D::draw(const RID &p_to_rid, const Color &p_color) {
	Vector<Vector2> points = _get_points();
	Vector<Color> col;
	col.push_back(p_color);
	RenderingServer::get_singleton()->canvas_item_add_polygon(p_to_rid, points, col);
}

Rect2 CapsuleShape2D::get_rect() const {
	Vector2 he = Point2(get_radius(), get_radius() + get_height() * 0.5);
	Rect2 rect;
	rect.position = -he;
	rect.size = he * 2.0;
	return rect;
}

real_t CapsuleShape2D::get_enclosing_radius() const {
	return radius + height * 0.5;
}

void CapsuleShape2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_radius", "radius"), &CapsuleShape2D::set_radius);
	ClassDB::bind_method(D_METHOD("get_radius"), &CapsuleShape2D::get_radius);

	ClassDB::bind_method(D_METHOD("set_height", "height"), &CapsuleShape2D::set_height);
	ClassDB::bind_method(D_METHOD("get_height"), &CapsuleShape2D::get_height);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius"), "set_radius", "get_radius");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "height"), "set_height", "get_height");
}

CapsuleShape2D::CapsuleShape2D() :
		Shape2D(PhysicsServer2D::get_singleton()->capsule_shape_create()) {
	radius = 10;
	height = 20;
	_update_shape();
}
