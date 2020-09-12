
/*  navigation_obstacle_3d.h                                             */

#ifndef NAVIGATION_OBSTACLE_H
#define NAVIGATION_OBSTACLE_H

#include "scene/main/node.h"

class Navigation3D;

class NavigationObstacle3D : public Node {
	GDCLASS(NavigationObstacle3D, Node);

	Navigation3D *navigation = nullptr;

	RID agent;

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	NavigationObstacle3D();
	virtual ~NavigationObstacle3D();

	void set_navigation(Navigation3D *p_nav);
	const Navigation3D *get_navigation() const {
		return navigation;
	}

	void set_navigation_node(Node *p_nav);
	Node *get_navigation_node() const;

	RID get_rid() const {
		return agent;
	}

	virtual String get_configuration_warning() const override;

private:
	void update_agent_shape();
};

#endif
