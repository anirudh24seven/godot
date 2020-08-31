
/*  register_types.cpp                                                   */



#include "register_types.h"
#include "core/error_macros.h"
#include "core/project_settings.h"
#ifdef JAVASCRIPT_ENABLED
#include "emscripten.h"
#include "emws_client.h"
#include "emws_peer.h"
#include "emws_server.h"
#else
#include "wsl_client.h"
#include "wsl_server.h"
#endif
#ifdef TOOLS_ENABLED
#include "editor/debugger/editor_debugger_server.h"
#include "editor/editor_node.h"
#include "editor_debugger_server_websocket.h"
#endif

#ifdef TOOLS_ENABLED
static void _editor_init_callback() {
	EditorDebuggerServer::register_protocol_handler("ws://", EditorDebuggerServerWebSocket::create);
}
#endif

void register_websocket_types() {
#ifdef JAVASCRIPT_ENABLED
	EMWSPeer::make_default();
	EMWSClient::make_default();
	EMWSServer::make_default();
#else
	WSLPeer::make_default();
	WSLClient::make_default();
	WSLServer::make_default();
#endif

	ClassDB::register_virtual_class<WebSocketMultiplayerPeer>();
	ClassDB::register_custom_instance_class<WebSocketServer>();
	ClassDB::register_custom_instance_class<WebSocketClient>();
	ClassDB::register_custom_instance_class<WebSocketPeer>();

#ifdef TOOLS_ENABLED
	EditorNode::add_init_callback(&_editor_init_callback);
#endif
}

void unregister_websocket_types() {}
