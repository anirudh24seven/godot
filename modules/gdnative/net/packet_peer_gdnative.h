
/*  packet_peer_gdnative.h                                               */



#ifndef PACKET_PEER_GDNATIVE_H
#define PACKET_PEER_GDNATIVE_H

#include "core/io/packet_peer.h"
#include "modules/gdnative/gdnative.h"
#include "modules/gdnative/include/net/godot_net.h"

class PacketPeerGDNative : public PacketPeer {
	GDCLASS(PacketPeerGDNative, PacketPeer);

protected:
	static void _bind_methods();
	const godot_net_packet_peer *interface;

public:
	PacketPeerGDNative();
	~PacketPeerGDNative();

	/* Sets the interface implementation from GDNative */
	void set_native_packet_peer(const godot_net_packet_peer *p_impl);

	/* Specific to PacketPeer */
	virtual Error get_packet(const uint8_t **r_buffer, int &r_buffer_size) override;
	virtual Error put_packet(const uint8_t *p_buffer, int p_buffer_size) override;
	virtual int get_max_packet_size() const override;
	virtual int get_available_packet_count() const override;
};

#endif // PACKET_PEER_GDNATIVE_H
