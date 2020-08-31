
/*  navigation_region_2d.h                                               */



#ifndef NAVIGATION_REGION_2D_H
#define NAVIGATION_REGION_2D_H

#include "scene/2d/node_2d.h"
#include "scene/resources/navigation_mesh.h"

class NavigationPolygon : public Resource {
	GDCLASS(NavigationPolygon, Resource);

	Vector<Vector2> vertices;
	struct Polygon {
		Vector<int> indices;
	};
	Vector<Polygon> polygons;
	Vector<Vector<Vector2>> outlines;

	mutable Rect2 item_rect;
	mutable bool rect_cache_dirty = true;

	Mutex navmesh_generation;
	// Navigation mesh
	Ref<NavigationMesh> navmesh;

protected:
	static void _bind_methods();

	void _set_polygons(const TypedArray<Vector<int32_t>> &p_array);
	Array _get_polygons() const;

	void _set_outlines(const TypedArray<Vector<Vector2>> &p_array);
	Array _get_outlines() const;

public:
#ifdef TOOLS_ENABLED
	Rect2 _edit_get_rect() const;
	bool _edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const;
#endif

	void set_vertices(const Vector<Vector2> &p_vertices);
	Vector<Vector2> get_vertices() const;

	void add_polygon(const Vector<int> &p_polygon);
	int get_polygon_count() const;

	void add_outline(const Vector<Vector2> &p_outline);
	void add_outline_at_index(const Vector<Vector2> &p_outline, int p_index);
	void set_outline(int p_idx, const Vector<Vector2> &p_outline);
	Vector<Vector2> get_outline(int p_idx) const;
	void remove_outline(int p_idx);
	int get_outline_count() const;

	void clear_outlines();
	void make_polygons_from_outlines();

	Vector<int> get_polygon(int p_idx);
	void clear_polygons();

	Ref<NavigationMesh> get_mesh();

	NavigationPolygon() {}
	~NavigationPolygon() {}
};

class Navigation2D;

class NavigationRegion2D : public Node2D {
	GDCLASS(NavigationRegion2D, Node2D);

	bool enabled = true;
	RID region;
	Navigation2D *navigation = nullptr;
	Ref<NavigationPolygon> navpoly;

	void _navpoly_changed();

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
#ifdef TOOLS_ENABLED
	virtual Rect2 _edit_get_rect() const override;
	virtual bool _edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const override;
#endif

	void set_enabled(bool p_enabled);
	bool is_enabled() const;

	void set_navigation_polygon(const Ref<NavigationPolygon> &p_navpoly);
	Ref<NavigationPolygon> get_navigation_polygon() const;

	String get_configuration_warning() const override;

	NavigationRegion2D();
	~NavigationRegion2D();
};

#endif // NAVIGATION_REGION_2D_H
