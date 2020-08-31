
/*  concave_polygon_shape_3d.h                                           */



#ifndef CONCAVE_POLYGON_SHAPE_3D_H
#define CONCAVE_POLYGON_SHAPE_3D_H

#include "scene/resources/shape_3d.h"

class ConcavePolygonShape3D : public Shape3D {
	GDCLASS(ConcavePolygonShape3D, Shape3D);

	struct DrawEdge {
		Vector3 a;
		Vector3 b;
		bool operator<(const DrawEdge &p_edge) const {
			if (a == p_edge.a) {
				return b < p_edge.b;
			} else {
				return a < p_edge.a;
			}
		}

		DrawEdge(const Vector3 &p_a = Vector3(), const Vector3 &p_b = Vector3()) {
			a = p_a;
			b = p_b;
			if (a < b) {
				SWAP(a, b);
			}
		}
	};

protected:
	static void _bind_methods();

	virtual void _update_shape() override;

public:
	void set_faces(const Vector<Vector3> &p_faces);
	Vector<Vector3> get_faces() const;

	virtual Vector<Vector3> get_debug_mesh_lines() const override;
	virtual real_t get_enclosing_radius() const override;

	ConcavePolygonShape3D();
};

#endif // CONCAVE_POLYGON_SHAPE_H
