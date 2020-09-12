
/*  editor_debugger_server.h                                             */

#ifndef EDITOR_DEBUGGER_CONNECTION_H
#define EDITOR_DEBUGGER_CONNECTION_H

#include "core/debugger/remote_debugger_peer.h"
#include "core/reference.h"

class EditorDebuggerServer : public Reference {
public:
	typedef EditorDebuggerServer *(*CreateServerFunc)(const String &p_uri);

private:
	static Map<StringName, CreateServerFunc> protocols;

public:
	static void initialize();
	static void deinitialize();

	static void register_protocol_handler(const String &p_protocol, CreateServerFunc p_func);
	static EditorDebuggerServer *create(const String &p_protocol);
	virtual void poll() = 0;
	virtual Error start() = 0;
	virtual void stop() = 0;
	virtual bool is_active() const = 0;
	virtual bool is_connection_available() const = 0;
	virtual Ref<RemoteDebuggerPeer> take_connection() = 0;
};

#endif // EDITOR_DEBUGGER_CONNECTION_H
