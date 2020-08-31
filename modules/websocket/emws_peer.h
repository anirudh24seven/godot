
/*  emws_peer.h                                                          */



#ifndef EMWSPEER_H
#define EMWSPEER_H

#ifdef JAVASCRIPT_ENABLED

#include "core/error_list.h"
#include "core/io/packet_peer.h"
#include "core/ring_buffer.h"
#include "emscripten.h"
#include "packet_buffer.h"
#include "websocket_peer.h"

class EMWSPeer : public WebSocketPeer {
	GDCIIMPL(EMWSPeer, WebSocketPeer);

private:
	int peer_sock;
	WriteMode write_mode;

	Vector<uint8_t> _packet_buffer;
	PacketBuffer<uint8_t> _in_buffer;
	uint8_t _is_string;

public:
	Error read_msg(uint8_t *p_data, uint32_t p_size, bool p_is_string);
	void set_sock(int p_sock, unsigned int p_in_buf_size, unsigned int p_in_pkt_size);
	virtual int get_available_packet_count() const;
	virtual Error get_packet(const uint8_t **r_buffer, int &r_buffer_size);
	virtual Error put_packet(const uint8_t *p_buffer, int p_buffer_size);
	virtual int get_max_packet_size() const { return _packet_buffer.size(); };

	virtual void close(int p_code = 1000, String p_reason = "");
	virtual bool is_connected_to_host() const;
	virtual IP_Address get_connected_host() const;
	virtual uint16_t get_connected_port() const;

	virtual WriteMode get_write_mode() const;
	virtual void set_write_mode(WriteMode p_mode);
	virtual bool was_string_packet() const;
	virtual void set_no_delay(bool p_enabled);

	EMWSPeer();
	~EMWSPeer();
};

#endif // JAVASCRIPT_ENABLED

#endif // LSWPEER_H
