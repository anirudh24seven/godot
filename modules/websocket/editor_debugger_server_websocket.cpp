
/*  editor_debugger_server_websocket.cpp                                 */

#include "editor_debugger_server_websocket.h"

#include "core/project_settings.h"
#include "editor/editor_settings.h"
#include "modules/websocket/remote_debugger_peer_websocket.h"

void EditorDebuggerServerWebSocket::_peer_connected(int p_id, String _protocol) {
	pending_peers.push_back(p_id);
}

void EditorDebuggerServerWebSocket::_peer_disconnected(int p_id, bool p_was_clean) {
	if (pending_peers.find(p_id)) {
		pending_peers.erase(p_id);
	}
}

void EditorDebuggerServerWebSocket::poll() {
	server->poll();
}

Error EditorDebuggerServerWebSocket::start() {
	int remote_port = (int)EditorSettings::get_singleton()->get("network/debug/remote_port");
	Vector<String> protocols;
	protocols.push_back("binary"); // compatibility with EMSCRIPTEN TCP-to-WebSocket layer.
	return server->listen(remote_port, protocols);
}

void EditorDebuggerServerWebSocket::stop() {
	server->stop();
	pending_peers.clear();
}

bool EditorDebuggerServerWebSocket::is_active() const {
	return server->is_listening();
}

bool EditorDebuggerServerWebSocket::is_connection_available() const {
	return pending_peers.size() > 0;
}

Ref<RemoteDebuggerPeer> EditorDebuggerServerWebSocket::take_connection() {
	ERR_FAIL_COND_V(!is_connection_available(), Ref<RemoteDebuggerPeer>());
	RemoteDebuggerPeer *peer = memnew(RemoteDebuggerPeerWebSocket(server->get_peer(pending_peers[0])));
	pending_peers.pop_front();
	return peer;
}

EditorDebuggerServerWebSocket::EditorDebuggerServerWebSocket() {
	server = Ref<WebSocketServer>(WebSocketServer::create());
	int max_pkts = (int)GLOBAL_GET("network/limits/debugger/max_queued_messages");
	server->set_buffers(8192, max_pkts, 8192, max_pkts);
	server->connect("client_connected", callable_mp(this, &EditorDebuggerServerWebSocket::_peer_connected));
	server->connect("client_disconnected", callable_mp(this, &EditorDebuggerServerWebSocket::_peer_disconnected));
}

EditorDebuggerServerWebSocket::~EditorDebuggerServerWebSocket() {
	stop();
}

EditorDebuggerServer *EditorDebuggerServerWebSocket::create(const String &p_protocol) {
	ERR_FAIL_COND_V(p_protocol != "ws://", nullptr);
	return memnew(EditorDebuggerServerWebSocket);
}
