
/*  remote_debugger_peer_websocket.h                                     */

#ifndef SCRIPT_DEBUGGER_WEBSOCKET_H
#define SCRIPT_DEBUGGER_WEBSOCKET_H

#ifdef JAVASCRIPT_ENABLED
#include "modules/websocket/emws_client.h"
#else
#include "modules/websocket/wsl_client.h"
#endif
#include "core/debugger/remote_debugger_peer.h"

class RemoteDebuggerPeerWebSocket : public RemoteDebuggerPeer {
	Ref<WebSocketClient> ws_client;
	Ref<WebSocketPeer> ws_peer;
	List<Array> in_queue;
	List<Array> out_queue;

	int max_queued_messages;

public:
	static RemoteDebuggerPeer *create(const String &p_uri);

	Error connect_to_host(const String &p_uri);
	bool is_peer_connected();
	int get_max_message_size() const;
	bool has_message();
	Error put_message(const Array &p_arr);
	Array get_message();
	void close();
	void poll();
	bool can_block() const;

	RemoteDebuggerPeerWebSocket(Ref<WebSocketPeer> p_peer = Ref<WebSocketPeer>());
};

#endif // SCRIPT_DEBUGGER_WEBSOCKET_H
