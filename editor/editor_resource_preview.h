
/*  editor_resource_preview.h                                            */

#ifndef EDITORRESOURCEPREVIEW_H
#define EDITORRESOURCEPREVIEW_H

#include "core/os/semaphore.h"
#include "core/os/thread.h"
#include "scene/main/node.h"
#include "scene/resources/texture.h"

class EditorResourcePreviewGenerator : public Reference {
	GDCLASS(EditorResourcePreviewGenerator, Reference);

protected:
	static void _bind_methods();

public:
	virtual bool handles(const String &p_type) const;
	virtual Ref<Texture2D> generate(const RES &p_from, const Size2 &p_size) const;
	virtual Ref<Texture2D> generate_from_path(const String &p_path, const Size2 &p_size) const;

	virtual bool generate_small_preview_automatically() const;
	virtual bool can_generate_small_preview() const;

	EditorResourcePreviewGenerator();
};

class EditorResourcePreview : public Node {
	GDCLASS(EditorResourcePreview, Node);

	static EditorResourcePreview *singleton;

	struct QueueItem {
		Ref<Resource> resource;
		String path;
		ObjectID id;
		StringName function;
		Variant userdata;
	};

	List<QueueItem> queue;

	Mutex preview_mutex;
	Semaphore preview_sem;
	Thread *thread;
	volatile bool exit;
	volatile bool exited;

	struct Item {
		Ref<Texture2D> preview;
		Ref<Texture2D> small_preview;
		int order;
		uint32_t last_hash;
		uint64_t modified_time;
	};

	int order;

	Map<String, Item> cache;

	void _preview_ready(const String &p_str, const Ref<Texture2D> &p_texture, const Ref<Texture2D> &p_small_texture, ObjectID id, const StringName &p_func, const Variant &p_ud);
	void _generate_preview(Ref<ImageTexture> &r_texture, Ref<ImageTexture> &r_small_texture, const QueueItem &p_item, const String &cache_base);

	static void _thread_func(void *ud);
	void _thread();

	Vector<Ref<EditorResourcePreviewGenerator>> preview_generators;

protected:
	static void _bind_methods();

public:
	static EditorResourcePreview *get_singleton();

	//callback function is callback(String p_path,Ref<Texture2D> preview,Variant udata) preview null if could not load
	void queue_resource_preview(const String &p_path, Object *p_receiver, const StringName &p_receiver_func, const Variant &p_userdata);
	void queue_edited_resource_preview(const Ref<Resource> &p_res, Object *p_receiver, const StringName &p_receiver_func, const Variant &p_userdata);

	void add_preview_generator(const Ref<EditorResourcePreviewGenerator> &p_generator);
	void remove_preview_generator(const Ref<EditorResourcePreviewGenerator> &p_generator);
	void check_for_invalidation(const String &p_path);

	void start();
	void stop();

	EditorResourcePreview();
	~EditorResourcePreview();
};

#endif // EDITORRESOURCEPREVIEW_H
