
/*  convex_polygon_shape_2d.cpp                                          */



#include "convex_polygon_shape_2d.h"

#include "core/math/geometry_2d.h"
#include "servers/physics_server_2d.h"
#include "servers/rendering_server.h"

bool ConvexPolygonShape2D::_edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const {
	return Geometry2D::is_point_in_polygon(p_point, points);
}

void ConvexPolygonShape2D::_update_shape() {
	Vector<Vector2> final_points = points;
	if (Geometry2D::is_polygon_clockwise(final_points)) { //needs to be counter clockwise
		final_points.invert();
	}
	PhysicsServer2D::get_singleton()->shape_set_data(get_rid(), final_points);
	emit_changed();
}

void ConvexPolygonShape2D::set_point_cloud(const Vector<Vector2> &p_points) {
	Vector<Point2> hull = Geometry2D::convex_hull(p_points);
	ERR_FAIL_COND(hull.size() < 3);
	set_points(hull);
}

void ConvexPolygonShape2D::set_points(const Vector<Vector2> &p_points) {
	points = p_points;

	_update_shape();
}

Vector<Vector2> ConvexPolygonShape2D::get_points() const {
	return points;
}

void ConvexPolygonShape2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_point_cloud", "point_cloud"), &ConvexPolygonShape2D::set_point_cloud);
	ClassDB::bind_method(D_METHOD("set_points", "points"), &ConvexPolygonShape2D::set_points);
	ClassDB::bind_method(D_METHOD("get_points"), &ConvexPolygonShape2D::get_points);

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR2_ARRAY, "points"), "set_points", "get_points");
}

void ConvexPolygonShape2D::draw(const RID &p_to_rid, const Color &p_color) {
	Vector<Color> col;
	col.push_back(p_color);
	RenderingServer::get_singleton()->canvas_item_add_polygon(p_to_rid, points, col);
}

Rect2 ConvexPolygonShape2D::get_rect() const {
	Rect2 rect;
	for (int i = 0; i < points.size(); i++) {
		if (i == 0) {
			rect.position = points[i];
		} else {
			rect.expand_to(points[i]);
		}
	}

	return rect;
}

real_t ConvexPolygonShape2D::get_enclosing_radius() const {
	real_t r = 0;
	for (int i(0); i < get_points().size(); i++) {
		r = MAX(get_points()[i].length_squared(), r);
	}
	return Math::sqrt(r);
}

ConvexPolygonShape2D::ConvexPolygonShape2D() :
		Shape2D(PhysicsServer2D::get_singleton()->convex_polygon_shape_create()) {
}
