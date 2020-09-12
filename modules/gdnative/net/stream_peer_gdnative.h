
/*  stream_peer_gdnative.h                                               */

#ifndef STREAM_PEER_GDNATIVE_H
#define STREAM_PEER_GDNATIVE_H

#include "core/io/stream_peer.h"
#include "modules/gdnative/gdnative.h"
#include "modules/gdnative/include/net/godot_net.h"

class StreamPeerGDNative : public StreamPeer {
	GDCLASS(StreamPeerGDNative, StreamPeer);

protected:
	static void _bind_methods();
	const godot_net_stream_peer *interface;

public:
	StreamPeerGDNative();
	~StreamPeerGDNative();

	/* Sets the interface implementation from GDNative */
	void set_native_stream_peer(const godot_net_stream_peer *p_interface);

	/* Specific to StreamPeer */
	Error put_data(const uint8_t *p_data, int p_bytes) override;
	Error put_partial_data(const uint8_t *p_data, int p_bytes, int &r_sent) override;
	Error get_data(uint8_t *p_buffer, int p_bytes) override;
	Error get_partial_data(uint8_t *p_buffer, int p_bytes, int &r_received) override;
	int get_available_bytes() const override;
};

#endif // STREAM_PEER_GDNATIVE_H
