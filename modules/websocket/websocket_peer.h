
/*  websocket_peer.h                                                     */



#ifndef WEBSOCKETPEER_H
#define WEBSOCKETPEER_H

#include "core/error_list.h"
#include "core/io/packet_peer.h"
#include "websocket_macros.h"

class WebSocketPeer : public PacketPeer {
	GDCLASS(WebSocketPeer, PacketPeer);
	GDCICLASS(WebSocketPeer);

public:
	enum WriteMode {
		WRITE_MODE_TEXT,
		WRITE_MODE_BINARY,
	};

protected:
	static void _bind_methods();

public:
	virtual WriteMode get_write_mode() const = 0;
	virtual void set_write_mode(WriteMode p_mode) = 0;

	virtual void close(int p_code = 1000, String p_reason = "") = 0;

	virtual bool is_connected_to_host() const = 0;
	virtual IP_Address get_connected_host() const = 0;
	virtual uint16_t get_connected_port() const = 0;
	virtual bool was_string_packet() const = 0;
	virtual void set_no_delay(bool p_enabled) = 0;

	WebSocketPeer();
	~WebSocketPeer();
};

VARIANT_ENUM_CAST(WebSocketPeer::WriteMode);
#endif // WEBSOCKETPEER_H
