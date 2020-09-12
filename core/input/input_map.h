
/*  input_map.h                                                          */

#ifndef INPUT_MAP_H
#define INPUT_MAP_H

#include "core/input/input_event.h"
#include "core/object.h"

class InputMap : public Object {
	GDCLASS(InputMap, Object);

public:
	/**
	* A special value used to signify that a given Action can be triggered by any device
	*/
	static int ALL_DEVICES;

	struct Action {
		int id;
		float deadzone;
		List<Ref<InputEvent>> inputs;
	};

private:
	static InputMap *singleton;

	mutable Map<StringName, Action> input_map;

	List<Ref<InputEvent>>::Element *_find_event(Action &p_action, const Ref<InputEvent> &p_event, bool *p_pressed = nullptr, float *p_strength = nullptr) const;

	Array _action_get_events(const StringName &p_action);
	Array _get_actions();

protected:
	static void _bind_methods();

public:
	static _FORCE_INLINE_ InputMap *get_singleton() { return singleton; }

	bool has_action(const StringName &p_action) const;
	List<StringName> get_actions() const;
	void add_action(const StringName &p_action, float p_deadzone = 0.5);
	void erase_action(const StringName &p_action);

	void action_set_deadzone(const StringName &p_action, float p_deadzone);
	void action_add_event(const StringName &p_action, const Ref<InputEvent> &p_event);
	bool action_has_event(const StringName &p_action, const Ref<InputEvent> &p_event);
	void action_erase_event(const StringName &p_action, const Ref<InputEvent> &p_event);
	void action_erase_events(const StringName &p_action);

	const List<Ref<InputEvent>> *action_get_events(const StringName &p_action);
	bool event_is_action(const Ref<InputEvent> &p_event, const StringName &p_action) const;
	bool event_get_action_status(const Ref<InputEvent> &p_event, const StringName &p_action, bool *p_pressed = nullptr, float *p_strength = nullptr) const;

	const Map<StringName, Action> &get_action_map() const;
	void load_from_globals();
	void load_default();

	InputMap();
};

#endif // INPUT_MAP_H
