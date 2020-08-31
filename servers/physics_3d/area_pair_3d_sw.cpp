
/*  area_pair_3d_sw.cpp                                                  */



#include "area_pair_3d_sw.h"
#include "collision_solver_3d_sw.h"

bool AreaPair3DSW::setup(real_t p_step) {
	bool result = false;

	if (area->is_shape_set_as_disabled(area_shape) || body->is_shape_set_as_disabled(body_shape)) {
		result = false;
	} else if (area->test_collision_mask(body) && CollisionSolver3DSW::solve_static(body->get_shape(body_shape), body->get_transform() * body->get_shape_transform(body_shape), area->get_shape(area_shape), area->get_transform() * area->get_shape_transform(area_shape), nullptr, this)) {
		result = true;
	}

	if (result != colliding) {
		if (result) {
			if (area->get_space_override_mode() != PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED) {
				body->add_area(area);
			}
			if (area->has_monitor_callback()) {
				area->add_body_to_query(body, body_shape, area_shape);
			}

		} else {
			if (area->get_space_override_mode() != PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED) {
				body->remove_area(area);
			}
			if (area->has_monitor_callback()) {
				area->remove_body_from_query(body, body_shape, area_shape);
			}
		}

		colliding = result;
	}

	return false; //never do any post solving
}

void AreaPair3DSW::solve(real_t p_step) {
}

AreaPair3DSW::AreaPair3DSW(Body3DSW *p_body, int p_body_shape, Area3DSW *p_area, int p_area_shape) {
	body = p_body;
	area = p_area;
	body_shape = p_body_shape;
	area_shape = p_area_shape;
	colliding = false;
	body->add_constraint(this, 0);
	area->add_constraint(this);
	if (p_body->get_mode() == PhysicsServer3D::BODY_MODE_KINEMATIC) {
		p_body->set_active(true);
	}
}

AreaPair3DSW::~AreaPair3DSW() {
	if (colliding) {
		if (area->get_space_override_mode() != PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED) {
			body->remove_area(area);
		}
		if (area->has_monitor_callback()) {
			area->remove_body_from_query(body, body_shape, area_shape);
		}
	}
	body->remove_constraint(this);
	area->remove_constraint(this);
}

////////////////////////////////////////////////////

bool Area2Pair3DSW::setup(real_t p_step) {
	bool result = false;
	if (area_a->is_shape_set_as_disabled(shape_a) || area_b->is_shape_set_as_disabled(shape_b)) {
		result = false;
	} else if (area_a->test_collision_mask(area_b) && CollisionSolver3DSW::solve_static(area_a->get_shape(shape_a), area_a->get_transform() * area_a->get_shape_transform(shape_a), area_b->get_shape(shape_b), area_b->get_transform() * area_b->get_shape_transform(shape_b), nullptr, this)) {
		result = true;
	}

	if (result != colliding) {
		if (result) {
			if (area_b->has_area_monitor_callback() && area_a->is_monitorable()) {
				area_b->add_area_to_query(area_a, shape_a, shape_b);
			}

			if (area_a->has_area_monitor_callback() && area_b->is_monitorable()) {
				area_a->add_area_to_query(area_b, shape_b, shape_a);
			}

		} else {
			if (area_b->has_area_monitor_callback() && area_a->is_monitorable()) {
				area_b->remove_area_from_query(area_a, shape_a, shape_b);
			}

			if (area_a->has_area_monitor_callback() && area_b->is_monitorable()) {
				area_a->remove_area_from_query(area_b, shape_b, shape_a);
			}
		}

		colliding = result;
	}

	return false; //never do any post solving
}

void Area2Pair3DSW::solve(real_t p_step) {
}

Area2Pair3DSW::Area2Pair3DSW(Area3DSW *p_area_a, int p_shape_a, Area3DSW *p_area_b, int p_shape_b) {
	area_a = p_area_a;
	area_b = p_area_b;
	shape_a = p_shape_a;
	shape_b = p_shape_b;
	colliding = false;
	area_a->add_constraint(this);
	area_b->add_constraint(this);
}

Area2Pair3DSW::~Area2Pair3DSW() {
	if (colliding) {
		if (area_b->has_area_monitor_callback()) {
			area_b->remove_area_from_query(area_a, shape_a, shape_b);
		}

		if (area_a->has_area_monitor_callback()) {
			area_a->remove_area_from_query(area_b, shape_b, shape_a);
		}
	}

	area_a->remove_constraint(this);
	area_b->remove_constraint(this);
}
