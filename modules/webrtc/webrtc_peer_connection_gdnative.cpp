
/*  webrtc_peer_connection_gdnative.cpp                                  */

#ifdef WEBRTC_GDNATIVE_ENABLED

#include "webrtc_peer_connection_gdnative.h"

#include "core/io/resource_loader.h"
#include "modules/gdnative/nativescript/nativescript.h"
#include "webrtc_data_channel_gdnative.h"

const godot_net_webrtc_library *WebRTCPeerConnectionGDNative::default_library = nullptr;

Error WebRTCPeerConnectionGDNative::set_default_library(const godot_net_webrtc_library *p_lib) {
	if (default_library) {
		const godot_net_webrtc_library *old = default_library;
		default_library = nullptr;
		old->unregistered();
	}
	default_library = p_lib;
	return OK; // Maybe add version check and fail accordingly
}

WebRTCPeerConnection *WebRTCPeerConnectionGDNative::_create() {
	WebRTCPeerConnectionGDNative *obj = memnew(WebRTCPeerConnectionGDNative);
	ERR_FAIL_COND_V_MSG(!default_library, obj, "Default GDNative WebRTC implementation not defined.");

	// Call GDNative constructor
	Error err = (Error)default_library->create_peer_connection(obj);
	ERR_FAIL_COND_V_MSG(err != OK, obj, "GDNative default library constructor returned an error.");

	return obj;
}

void WebRTCPeerConnectionGDNative::_bind_methods() {
}

WebRTCPeerConnectionGDNative::WebRTCPeerConnectionGDNative() {
	interface = nullptr;
}

WebRTCPeerConnectionGDNative::~WebRTCPeerConnectionGDNative() {
}

Error WebRTCPeerConnectionGDNative::initialize(Dictionary p_config) {
	ERR_FAIL_COND_V(interface == nullptr, ERR_UNCONFIGURED);
	return (Error)interface->initialize(interface->data, (const godot_dictionary *)&p_config);
}

Ref<WebRTCDataChannel> WebRTCPeerConnectionGDNative::create_data_channel(String p_label, Dictionary p_options) {
	ERR_FAIL_COND_V(interface == nullptr, nullptr);
	return (WebRTCDataChannel *)interface->create_data_channel(interface->data, p_label.utf8().get_data(), (const godot_dictionary *)&p_options);
}

Error WebRTCPeerConnectionGDNative::create_offer() {
	ERR_FAIL_COND_V(interface == nullptr, ERR_UNCONFIGURED);
	return (Error)interface->create_offer(interface->data);
}

Error WebRTCPeerConnectionGDNative::set_local_description(String p_type, String p_sdp) {
	ERR_FAIL_COND_V(interface == nullptr, ERR_UNCONFIGURED);
	return (Error)interface->set_local_description(interface->data, p_type.utf8().get_data(), p_sdp.utf8().get_data());
}

Error WebRTCPeerConnectionGDNative::set_remote_description(String p_type, String p_sdp) {
	ERR_FAIL_COND_V(interface == nullptr, ERR_UNCONFIGURED);
	return (Error)interface->set_remote_description(interface->data, p_type.utf8().get_data(), p_sdp.utf8().get_data());
}

Error WebRTCPeerConnectionGDNative::add_ice_candidate(String sdpMidName, int sdpMlineIndexName, String sdpName) {
	ERR_FAIL_COND_V(interface == nullptr, ERR_UNCONFIGURED);
	return (Error)interface->add_ice_candidate(interface->data, sdpMidName.utf8().get_data(), sdpMlineIndexName, sdpName.utf8().get_data());
}

Error WebRTCPeerConnectionGDNative::poll() {
	ERR_FAIL_COND_V(interface == nullptr, ERR_UNCONFIGURED);
	return (Error)interface->poll(interface->data);
}

void WebRTCPeerConnectionGDNative::close() {
	ERR_FAIL_COND(interface == nullptr);
	interface->close(interface->data);
}

WebRTCPeerConnection::ConnectionState WebRTCPeerConnectionGDNative::get_connection_state() const {
	ERR_FAIL_COND_V(interface == nullptr, STATE_DISCONNECTED);
	return (ConnectionState)interface->get_connection_state(interface->data);
}

void WebRTCPeerConnectionGDNative::set_native_webrtc_peer_connection(const godot_net_webrtc_peer_connection *p_impl) {
	interface = p_impl;
}

#endif // WEBRTC_GDNATIVE_ENABLED
