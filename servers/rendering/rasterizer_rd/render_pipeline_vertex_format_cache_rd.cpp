
/*  render_pipeline_vertex_format_cache_rd.cpp                           */

#include "render_pipeline_vertex_format_cache_rd.h"
#include "core/os/memory.h"

RID RenderPipelineVertexFormatCacheRD::_generate_version(RD::VertexFormatID p_vertex_format_id, RD::FramebufferFormatID p_framebuffer_format_id, bool p_wireframe) {
	RD::PipelineMultisampleState multisample_state_version = multisample_state;
	multisample_state_version.sample_count = RD::get_singleton()->framebuffer_format_get_texture_samples(p_framebuffer_format_id);

	RD::PipelineRasterizationState raster_state_version = rasterization_state;
	raster_state_version.wireframe = p_wireframe;

	RID pipeline = RD::get_singleton()->render_pipeline_create(shader, p_framebuffer_format_id, p_vertex_format_id, render_primitive, raster_state_version, multisample_state_version, depth_stencil_state, blend_state, dynamic_state_flags);
	ERR_FAIL_COND_V(pipeline.is_null(), RID());
	versions = (Version *)memrealloc(versions, sizeof(Version) * (version_count + 1));
	versions[version_count].framebuffer_id = p_framebuffer_format_id;
	versions[version_count].vertex_id = p_vertex_format_id;
	versions[version_count].wireframe = p_wireframe;
	versions[version_count].pipeline = pipeline;
	version_count++;
	return pipeline;
}

void RenderPipelineVertexFormatCacheRD::_clear() {
	if (versions) {
		for (uint32_t i = 0; i < version_count; i++) {
			//shader may be gone, so this may not be valid
			if (RD::get_singleton()->render_pipeline_is_valid(versions[i].pipeline)) {
				RD::get_singleton()->free(versions[i].pipeline);
			}
		}
		version_count = 0;
		memfree(versions);
		versions = nullptr;
	}
}

void RenderPipelineVertexFormatCacheRD::setup(RID p_shader, RD::RenderPrimitive p_primitive, const RD::PipelineRasterizationState &p_rasterization_state, RD::PipelineMultisampleState p_multisample, const RD::PipelineDepthStencilState &p_depth_stencil_state, const RD::PipelineColorBlendState &p_blend_state, int p_dynamic_state_flags) {
	ERR_FAIL_COND(p_shader.is_null());
	_clear();
	shader = p_shader;
	input_mask = RD::get_singleton()->shader_get_vertex_input_attribute_mask(p_shader);
	render_primitive = p_primitive;
	rasterization_state = p_rasterization_state;
	multisample_state = p_multisample;
	depth_stencil_state = p_depth_stencil_state;
	blend_state = p_blend_state;
	dynamic_state_flags = p_dynamic_state_flags;
}

void RenderPipelineVertexFormatCacheRD::update_shader(RID p_shader) {
	ERR_FAIL_COND(p_shader.is_null());
	_clear();
	setup(p_shader, render_primitive, rasterization_state, multisample_state, depth_stencil_state, blend_state, dynamic_state_flags);
}

void RenderPipelineVertexFormatCacheRD::clear() {
	_clear();
	shader = RID(); //clear shader
	input_mask = 0;
}

RenderPipelineVertexFormatCacheRD::RenderPipelineVertexFormatCacheRD() {
	version_count = 0;
	versions = nullptr;
	input_mask = 0;
}

RenderPipelineVertexFormatCacheRD::~RenderPipelineVertexFormatCacheRD() {
	_clear();
}
