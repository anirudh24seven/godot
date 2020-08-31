
/*  audio_stream_editor_plugin.h                                         */



#ifndef AUDIO_STREAM_EDITOR_PLUGIN_H
#define AUDIO_STREAM_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/audio/audio_stream_player.h"
#include "scene/gui/color_rect.h"
#include "scene/resources/texture.h"

class AudioStreamEditor : public ColorRect {
	GDCLASS(AudioStreamEditor, ColorRect);

	Ref<AudioStream> stream;
	AudioStreamPlayer *_player;
	ColorRect *_preview;
	Control *_indicator;
	Label *_current_label;
	Label *_duration_label;

	Button *_play_button;
	Button *_stop_button;

	float _current;
	bool _dragging;

protected:
	void _notification(int p_what);
	void _preview_changed(ObjectID p_which);
	void _play();
	void _stop();
	void _on_finished();
	void _draw_preview();
	void _draw_indicator();
	void _on_input_indicator(Ref<InputEvent> p_event);
	void _seek_to(real_t p_x);
	void _changed_callback(Object *p_changed, const char *p_prop) override;
	static void _bind_methods();

public:
	void edit(Ref<AudioStream> p_stream);
	AudioStreamEditor();
};

class AudioStreamEditorPlugin : public EditorPlugin {
	GDCLASS(AudioStreamEditorPlugin, EditorPlugin);

	AudioStreamEditor *audio_editor;
	EditorNode *editor;

public:
	virtual String get_name() const override { return "Audio"; }
	bool has_main_screen() const override { return false; }
	virtual void edit(Object *p_object) override;
	virtual bool handles(Object *p_object) const override;
	virtual void make_visible(bool p_visible) override;

	AudioStreamEditorPlugin(EditorNode *p_node);
	~AudioStreamEditorPlugin();
};

#endif // AUDIO_STREAM_EDITOR_PLUGIN_H
