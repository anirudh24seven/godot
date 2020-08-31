
/*  remote_debugger_peer.h                                               */



#ifndef REMOTE_DEBUGGER_PEER_H
#define REMOTE_DEBUGGER_PEER_H

#include "core/io/stream_peer_tcp.h"
#include "core/os/mutex.h"
#include "core/os/thread.h"
#include "core/reference.h"
#include "core/ustring.h"

class RemoteDebuggerPeer : public Reference {
protected:
	int max_queued_messages = 4096;

public:
	virtual bool is_peer_connected() = 0;
	virtual bool has_message() = 0;
	virtual Error put_message(const Array &p_arr) = 0;
	virtual Array get_message() = 0;
	virtual void close() = 0;
	virtual void poll() = 0;
	virtual int get_max_message_size() const = 0;
	virtual bool can_block() const { return true; } // If blocking io is allowed on main thread (debug).

	RemoteDebuggerPeer();
};

class RemoteDebuggerPeerTCP : public RemoteDebuggerPeer {
private:
	Ref<StreamPeerTCP> tcp_client;
	Mutex mutex;
	Thread *thread = nullptr;
	List<Array> in_queue;
	List<Array> out_queue;
	int out_left = 0;
	int out_pos = 0;
	Vector<uint8_t> out_buf;
	int in_left = 0;
	int in_pos = 0;
	Vector<uint8_t> in_buf;
	bool connected = false;
	bool running = false;

	static void _thread_func(void *p_ud);

	void _poll();
	void _write_out();
	void _read_in();

public:
	static RemoteDebuggerPeer *create(const String &p_uri);

	Error connect_to_host(const String &p_host, uint16_t p_port);

	void poll();
	bool is_peer_connected();
	bool has_message();
	Array get_message();
	Error put_message(const Array &p_arr);
	int get_max_message_size() const;
	void close();

	RemoteDebuggerPeerTCP(Ref<StreamPeerTCP> p_stream = Ref<StreamPeerTCP>());
	~RemoteDebuggerPeerTCP();
};

#endif // REMOTE_DEBUGGER_PEER_H
