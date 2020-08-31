
/*  webrtc_peer_connection_gdnative.h                                    */



#ifdef WEBRTC_GDNATIVE_ENABLED

#ifndef WEBRTC_PEER_CONNECTION_GDNATIVE_H
#define WEBRTC_PEER_CONNECTION_GDNATIVE_H

#include "modules/gdnative/include/net/godot_net.h"
#include "webrtc_peer_connection.h"

class WebRTCPeerConnectionGDNative : public WebRTCPeerConnection {
	GDCLASS(WebRTCPeerConnectionGDNative, WebRTCPeerConnection);

protected:
	static void _bind_methods();
	static WebRTCPeerConnection *_create();

private:
	static const godot_net_webrtc_library *default_library;
	const godot_net_webrtc_peer_connection *interface;

public:
	static Error set_default_library(const godot_net_webrtc_library *p_library);
	static void make_default() { WebRTCPeerConnection::_create = WebRTCPeerConnectionGDNative::_create; }

	void set_native_webrtc_peer_connection(const godot_net_webrtc_peer_connection *p_impl);

	virtual ConnectionState get_connection_state() const override;

	virtual Error initialize(Dictionary p_config = Dictionary()) override;
	virtual Ref<WebRTCDataChannel> create_data_channel(String p_label, Dictionary p_options = Dictionary()) override;
	virtual Error create_offer() override;
	virtual Error set_remote_description(String type, String sdp) override;
	virtual Error set_local_description(String type, String sdp) override;
	virtual Error add_ice_candidate(String sdpMidName, int sdpMlineIndexName, String sdpName) override;
	virtual Error poll() override;
	virtual void close() override;

	WebRTCPeerConnectionGDNative();
	~WebRTCPeerConnectionGDNative();
};

#endif // WEBRTC_PEER_CONNECTION_GDNATIVE_H

#endif // WEBRTC_GDNATIVE_ENABLED
