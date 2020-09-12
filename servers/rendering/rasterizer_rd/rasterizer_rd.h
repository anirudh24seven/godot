
/*  rasterizer_rd.h                                                      */

#ifndef RASTERIZER_RD_H
#define RASTERIZER_RD_H

#include "core/os/os.h"
#include "core/thread_work_pool.h"
#include "servers/rendering/rasterizer.h"
#include "servers/rendering/rasterizer_rd/rasterizer_canvas_rd.h"
#include "servers/rendering/rasterizer_rd/rasterizer_scene_high_end_rd.h"
#include "servers/rendering/rasterizer_rd/rasterizer_storage_rd.h"

class RasterizerRD : public Rasterizer {
protected:
	RasterizerCanvasRD *canvas;
	RasterizerStorageRD *storage;
	RasterizerSceneHighEndRD *scene;

	RID copy_viewports_rd_shader;
	RID copy_viewports_rd_pipeline;
	RID copy_viewports_rd_index_buffer;
	RID copy_viewports_rd_array;
	RID copy_viewports_sampler;

	Map<RID, RID> render_target_descriptors;

	double time;
	float delta;

	static uint64_t frame;

public:
	RasterizerStorage *get_storage() { return storage; }
	RasterizerCanvas *get_canvas() { return canvas; }
	RasterizerScene *get_scene() { return scene; }

	void set_boot_image(const Ref<Image> &p_image, const Color &p_color, bool p_scale, bool p_use_filter) {}

	void initialize();
	void begin_frame(double frame_step);
	void prepare_for_blitting_render_targets();
	void blit_render_targets_to_screen(DisplayServer::WindowID p_screen, const BlitToScreen *p_render_targets, int p_amount);

	void end_frame(bool p_swap_buffers);
	void finalize();

	_ALWAYS_INLINE_ uint64_t get_frame_number() const { return frame; }
	_ALWAYS_INLINE_ float get_frame_delta_time() const { return delta; }
	_ALWAYS_INLINE_ double get_total_time() const { return time; }

	static Error is_viable() {
		return OK;
	}

	static Rasterizer *_create_current() {
		return memnew(RasterizerRD);
	}

	static void make_current() {
		_create_func = _create_current;
	}

	virtual bool is_low_end() const { return false; }

	static ThreadWorkPool thread_work_pool;

	static RasterizerRD *singleton;
	RasterizerRD();
	~RasterizerRD() {}
};
#endif // RASTERIZER_RD_H
