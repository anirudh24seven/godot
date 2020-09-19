
/*  webrtc_multiplayer.h                                                 */

#ifndef WEBRTC_MULTIPLAYER_H
#define WEBRTC_MULTIPLAYER_H

#include "core/io/networked_multiplayer_peer.h"
#include "webrtc_peer_connection.h"

class WebRTCMultiplayer : public NetworkedMultiplayerPeer {
	GDCLASS(WebRTCMultiplayer, NetworkedMultiplayerPeer);

protected:
	static void _bind_methods();

private:
	enum {
		CH_RELIABLE = 0,
		CH_ORDERED = 1,
		CH_UNRELIABLE = 2,
		CH_RESERVED_MAX = 3
	};

	class ConnectedPeer : public Reference {
	public:
		Ref<WebRTCPeerConnection> connection;
		List<Ref<WebRTCDataChannel>> channels;
		bool connected;

		ConnectedPeer() {
			connected = false;
			for (int i = 0; i < CH_RESERVED_MAX; i++) {
				channels.push_front(Ref<WebRTCDataChannel>());
			}
		}
	};

	uint32_t unique_id;
	int target_peer;
	int client_count;
	bool refuse_connections;
	ConnectionStatus connection_status;
	TransferMode transfer_mode;
	int next_packet_peer;
	bool server_compat;

	Map<int, Ref<ConnectedPeer>> peer_map;

	void _peer_to_dict(Ref<ConnectedPeer> p_connected_peer, Dictionary &r_dict);
	void _find_next_peer();

public:
	WebRTCMultiplayer();
	~WebRTCMultiplayer();

	Error initialize(int p_self_id, bool p_server_compat = false);
	Error add_peer(Ref<WebRTCPeerConnection> p_peer, int p_peer_id, int p_unreliable_lifetime = 1);
	void remove_peer(int p_peer_id);
	bool has_peer(int p_peer_id);
	Dictionary get_peer(int p_peer_id);
	Dictionary get_peers();
	void close();

	// PacketPeer
	Error get_packet(const uint8_t **r_buffer, int &r_buffer_size) override; ///< buffer is GONE after next get_packet
	Error put_packet(const uint8_t *p_buffer, int p_buffer_size) override;
	int get_available_packet_count() const override;
	int get_max_packet_size() const override;

	// NetworkedMultiplayerPeer
	void set_transfer_mode(TransferMode p_mode) override;
	TransferMode get_transfer_mode() const override;
	void set_target_peer(int p_peer_id) override;

	int get_unique_id() const override;
	int get_packet_peer() const override;

	bool is_server() const override;

	void poll() override;

	void set_refuse_new_connections(bool p_enable) override;
	bool is_refusing_new_connections() const override;

	ConnectionStatus get_connection_status() const override;
};

#endif // WEBRTC_MULTIPLAYER_H
