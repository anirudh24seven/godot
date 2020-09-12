
/*  editor_performance_profiler.h                                        */

#ifndef EDITOR_PERFORMANCE_PROFILER_H
#define EDITOR_PERFORMANCE_PROFILER_H

#include "core/map.h"
#include "core/ordered_hash_map.h"
#include "main/performance.h"
#include "scene/gui/control.h"
#include "scene/gui/label.h"
#include "scene/gui/split_container.h"
#include "scene/gui/tree.h"

class EditorPerformanceProfiler : public HSplitContainer {
	GDCLASS(EditorPerformanceProfiler, HSplitContainer);

private:
	class Monitor {
	public:
		String name;
		String base;
		List<float> history;
		float max = 0.0f;
		TreeItem *item = nullptr;
		Performance::MonitorType type = Performance::MONITOR_TYPE_QUANTITY;
		int frame_index = 0;

		Monitor();
		Monitor(String p_name, String p_base, int p_frame_index, Performance::MonitorType p_type, TreeItem *p_item);
		void update_value(float p_value);
		void reset();
	};

	OrderedHashMap<StringName, Monitor> monitors;

	Map<StringName, TreeItem *> base_map;
	Tree *monitor_tree;
	Control *monitor_draw;
	Label *info_message;
	StringName marker_key;
	int marker_frame;
	const int MARGIN = 4;
	const int POINT_SEPARATION = 5;
	const int MARKER_MARGIN = 2;

	static String _create_label(float p_value, Performance::MonitorType p_type);
	void _monitor_select();
	void _monitor_draw();
	void _build_monitor_tree();
	TreeItem *_get_monitor_base(const StringName &p_base_name);
	TreeItem *_create_monitor_item(const StringName &p_monitor_name, TreeItem *p_base);
	void _marker_input(const Ref<InputEvent> &p_event);

public:
	void reset();
	void update_monitors(const Vector<StringName> &p_names);
	void add_profile_frame(const Vector<float> &p_values);
	List<float> *get_monitor_data(const StringName &p_name);
	EditorPerformanceProfiler();
};

#endif // EDITOR_PERFORMANCE_PROFILER_H
