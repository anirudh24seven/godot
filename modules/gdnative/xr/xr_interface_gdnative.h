
/*  xr_interface_gdnative.h                                              */



#ifndef XR_INTERFACE_GDNATIVE_H
#define XR_INTERFACE_GDNATIVE_H

#include "modules/gdnative/gdnative.h"
#include "servers/xr/xr_interface.h"

/**
	@authors Hinsbart & Karroffel & Mux213

	This subclass of our AR/VR interface forms a bridge to GDNative.
*/

class XRInterfaceGDNative : public XRInterface {
	GDCLASS(XRInterfaceGDNative, XRInterface);

	void cleanup();

protected:
	const godot_xr_interface_gdnative *interface;
	void *data;

	static void _bind_methods();

public:
	/** general interface information **/
	XRInterfaceGDNative();
	~XRInterfaceGDNative();

	void set_interface(const godot_xr_interface_gdnative *p_interface);

	virtual StringName get_name() const override;
	virtual int get_capabilities() const override;

	virtual bool is_initialized() const override;
	virtual bool initialize() override;
	virtual void uninitialize() override;

	/** specific to AR **/
	virtual bool get_anchor_detection_is_enabled() const override;
	virtual void set_anchor_detection_is_enabled(bool p_enable) override;
	virtual int get_camera_feed_id() override;

	/** rendering and internal **/
	virtual Size2 get_render_targetsize() override;
	virtual bool is_stereo() override;
	virtual Transform get_transform_for_eye(XRInterface::Eyes p_eye, const Transform &p_cam_transform) override;

	// we expose a Vector<float> version of this function to GDNative
	Vector<float> _get_projection_for_eye(XRInterface::Eyes p_eye, real_t p_aspect, real_t p_z_near, real_t p_z_far);

	// and a CameraMatrix version to XRServer
	virtual CameraMatrix get_projection_for_eye(XRInterface::Eyes p_eye, real_t p_aspect, real_t p_z_near, real_t p_z_far) override;

	virtual unsigned int get_external_texture_for_eye(XRInterface::Eyes p_eye) override;
	virtual void commit_for_eye(XRInterface::Eyes p_eye, RID p_render_target, const Rect2 &p_screen_rect) override;

	virtual void process() override;
	virtual void notification(int p_what) override;
};

#endif // XR_INTERFACE_GDNATIVE_H
