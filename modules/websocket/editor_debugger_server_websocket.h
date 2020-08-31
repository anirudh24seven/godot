
/*  editor_debugger_server_websocket.h                                   */



#ifndef SCRIPT_EDITOR_DEBUGGER_WEBSOCKET_H
#define SCRIPT_EDITOR_DEBUGGER_WEBSOCKET_H

#include "modules/websocket/websocket_server.h"

#include "editor/debugger/editor_debugger_server.h"

class EditorDebuggerServerWebSocket : public EditorDebuggerServer {
	GDCLASS(EditorDebuggerServerWebSocket, EditorDebuggerServer);

private:
	Ref<WebSocketServer> server;
	List<int> pending_peers;

public:
	static EditorDebuggerServer *create(const String &p_protocol);

	void _peer_connected(int p_peer, String p_protocol);
	void _peer_disconnected(int p_peer, bool p_was_clean);

	void poll() override;
	Error start() override;
	void stop() override;
	bool is_active() const override;
	bool is_connection_available() const override;
	Ref<RemoteDebuggerPeer> take_connection() override;

	EditorDebuggerServerWebSocket();
	~EditorDebuggerServerWebSocket();
};

#endif // SCRIPT_EDITOR_DEBUGGER_WEBSOCKET_H
