
/*  editor_debugger_server.cpp                                           */

#include "editor_debugger_server.h"

#include "core/io/marshalls.h"
#include "core/io/tcp_server.h"
#include "core/os/mutex.h"
#include "core/os/thread.h"
#include "editor/editor_log.h"
#include "editor/editor_node.h"
#include "editor/editor_settings.h"

class EditorDebuggerServerTCP : public EditorDebuggerServer {
private:
	Ref<TCP_Server> server;

public:
	static EditorDebuggerServer *create(const String &p_protocol);
	virtual void poll() {}
	virtual Error start();
	virtual void stop();
	virtual bool is_active() const;
	virtual bool is_connection_available() const;
	virtual Ref<RemoteDebuggerPeer> take_connection();

	EditorDebuggerServerTCP();
};

EditorDebuggerServer *EditorDebuggerServerTCP::create(const String &p_protocol) {
	ERR_FAIL_COND_V(p_protocol != "tcp://", nullptr);
	return memnew(EditorDebuggerServerTCP);
}

EditorDebuggerServerTCP::EditorDebuggerServerTCP() {
	server.instance();
}

Error EditorDebuggerServerTCP::start() {
	int remote_port = (int)EditorSettings::get_singleton()->get("network/debug/remote_port");
	const Error err = server->listen(remote_port);
	if (err != OK) {
		EditorNode::get_log()->add_message(String("Error listening on port ") + itos(remote_port), EditorLog::MSG_TYPE_ERROR);
		return err;
	}
	return err;
}

void EditorDebuggerServerTCP::stop() {
	server->stop();
}

bool EditorDebuggerServerTCP::is_active() const {
	return server->is_listening();
}

bool EditorDebuggerServerTCP::is_connection_available() const {
	return server->is_listening() && server->is_connection_available();
}

Ref<RemoteDebuggerPeer> EditorDebuggerServerTCP::take_connection() {
	ERR_FAIL_COND_V(!is_connection_available(), Ref<RemoteDebuggerPeer>());
	return memnew(RemoteDebuggerPeerTCP(server->take_connection()));
}

/// EditorDebuggerServer
Map<StringName, EditorDebuggerServer::CreateServerFunc> EditorDebuggerServer::protocols;

EditorDebuggerServer *EditorDebuggerServer::create(const String &p_protocol) {
	ERR_FAIL_COND_V(!protocols.has(p_protocol), nullptr);
	return protocols[p_protocol](p_protocol);
}

void EditorDebuggerServer::register_protocol_handler(const String &p_protocol, CreateServerFunc p_func) {
	ERR_FAIL_COND(protocols.has(p_protocol));
	protocols[p_protocol] = p_func;
}

void EditorDebuggerServer::initialize() {
	register_protocol_handler("tcp://", EditorDebuggerServerTCP::create);
}

void EditorDebuggerServer::deinitialize() {
	protocols.clear();
}
