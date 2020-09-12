
/*  file_access_network.h                                                */

#ifndef FILE_ACCESS_NETWORK_H
#define FILE_ACCESS_NETWORK_H

#include "core/io/stream_peer_tcp.h"
#include "core/os/file_access.h"
#include "core/os/semaphore.h"
#include "core/os/thread.h"

class FileAccessNetwork;

class FileAccessNetworkClient {
	struct BlockRequest {
		int id;
		uint64_t offset;
		int size;
	};

	List<BlockRequest> block_requests;

	Semaphore sem;
	Thread *thread = nullptr;
	bool quit = false;
	Mutex mutex;
	Mutex blockrequest_mutex;
	Map<int, FileAccessNetwork *> accesses;
	Ref<StreamPeerTCP> client;
	int last_id = 0;
	int lockcount = 0;

	Vector<uint8_t> block;

	void _thread_func();
	static void _thread_func(void *s);

	void put_32(int p_32);
	void put_64(int64_t p_64);
	int get_32();
	int64_t get_64();
	void lock_mutex();
	void unlock_mutex();

	friend class FileAccessNetwork;
	static FileAccessNetworkClient *singleton;

public:
	static FileAccessNetworkClient *get_singleton() { return singleton; }

	Error connect(const String &p_host, int p_port, const String &p_password = "");

	FileAccessNetworkClient();
	~FileAccessNetworkClient();
};

class FileAccessNetwork : public FileAccess {
	Semaphore sem;
	Semaphore page_sem;
	Mutex buffer_mutex;
	bool opened = false;
	size_t total_size;
	mutable size_t pos = 0;
	int id;
	mutable bool eof_flag = false;
	mutable int last_page = -1;
	mutable uint8_t *last_page_buff = nullptr;

	int page_size;
	int read_ahead;

	mutable int waiting_on_page = -1;

	struct Page {
		int activity = 0;
		bool queued = false;
		Vector<uint8_t> buffer;
	};

	mutable Vector<Page> pages;

	mutable Error response;

	uint64_t exists_modtime;
	friend class FileAccessNetworkClient;
	void _queue_page(int p_page) const;
	void _respond(size_t p_len, Error p_status);
	void _set_block(int p_offset, const Vector<uint8_t> &p_block);

public:
	enum Command {
		COMMAND_OPEN_FILE,
		COMMAND_READ_BLOCK,
		COMMAND_CLOSE,
		COMMAND_FILE_EXISTS,
		COMMAND_GET_MODTIME,
	};

	enum Response {
		RESPONSE_OPEN,
		RESPONSE_DATA,
		RESPONSE_FILE_EXISTS,
		RESPONSE_GET_MODTIME,
	};

	virtual Error _open(const String &p_path, int p_mode_flags); ///< open a file
	virtual void close(); ///< close a file
	virtual bool is_open() const; ///< true when file is open

	virtual void seek(size_t p_position); ///< seek to a given position
	virtual void seek_end(int64_t p_position = 0); ///< seek from the end of file
	virtual size_t get_position() const; ///< get position in the file
	virtual size_t get_len() const; ///< get size of the file

	virtual bool eof_reached() const; ///< reading passed EOF

	virtual uint8_t get_8() const; ///< get a byte
	virtual int get_buffer(uint8_t *p_dst, int p_length) const;

	virtual Error get_error() const; ///< get last error

	virtual void flush();
	virtual void store_8(uint8_t p_dest); ///< store a byte

	virtual bool file_exists(const String &p_path); ///< return true if a file exists

	virtual uint64_t _get_modified_time(const String &p_file);
	virtual uint32_t _get_unix_permissions(const String &p_file);
	virtual Error _set_unix_permissions(const String &p_file, uint32_t p_permissions);

	static void configure();

	FileAccessNetwork();
	~FileAccessNetwork();
};

#endif // FILE_ACCESS_NETWORK_H
