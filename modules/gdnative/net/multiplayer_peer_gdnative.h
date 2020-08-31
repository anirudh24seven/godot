
/*  multiplayer_peer_gdnative.h                                          */



#ifndef MULTIPLAYER_PEER_GDNATIVE_H
#define MULTIPLAYER_PEER_GDNATIVE_H

#include "core/io/networked_multiplayer_peer.h"
#include "modules/gdnative/gdnative.h"
#include "modules/gdnative/include/net/godot_net.h"

class MultiplayerPeerGDNative : public NetworkedMultiplayerPeer {
	GDCLASS(MultiplayerPeerGDNative, NetworkedMultiplayerPeer);

protected:
	static void _bind_methods();
	const godot_net_multiplayer_peer *interface;

public:
	MultiplayerPeerGDNative();
	~MultiplayerPeerGDNative();

	/* Sets the interface implementation from GDNative */
	void set_native_multiplayer_peer(const godot_net_multiplayer_peer *p_impl);

	/* Specific to PacketPeer */
	virtual Error get_packet(const uint8_t **r_buffer, int &r_buffer_size) override;
	virtual Error put_packet(const uint8_t *p_buffer, int p_buffer_size) override;
	virtual int get_max_packet_size() const override;
	virtual int get_available_packet_count() const override;

	/* Specific to NetworkedMultiplayerPeer */
	virtual void set_transfer_mode(TransferMode p_mode) override;
	virtual TransferMode get_transfer_mode() const override;
	virtual void set_target_peer(int p_peer_id) override;

	virtual int get_packet_peer() const override;

	virtual bool is_server() const override;

	virtual void poll() override;

	virtual int get_unique_id() const override;

	virtual void set_refuse_new_connections(bool p_enable) override;
	virtual bool is_refusing_new_connections() const override;

	virtual ConnectionStatus get_connection_status() const override;
};

#endif // MULTIPLAYER_PEER_GDNATIVE_H
