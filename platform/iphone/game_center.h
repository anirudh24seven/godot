
/*  game_center.h                                                        */



#ifdef GAME_CENTER_ENABLED

#ifndef GAME_CENTER_H
#define GAME_CENTER_H

#include "core/object.h"

class GameCenter : public Object {
	GDCLASS(GameCenter, Object);

	static GameCenter *instance;
	static void _bind_methods();

	List<Variant> pending_events;

	bool authenticated;

	void return_connect_error(const char *p_error_description);

public:
	void connect();
	bool is_authenticated();

	Error post_score(Dictionary p_score);
	Error award_achievement(Dictionary p_params);
	void reset_achievements();
	void request_achievements();
	void request_achievement_descriptions();
	Error show_game_center(Dictionary p_params);
	Error request_identity_verification_signature();

	void game_center_closed();

	int get_pending_event_count();
	Variant pop_pending_event();

	static GameCenter *get_singleton();

	GameCenter();
	~GameCenter();
};

#endif

#endif
