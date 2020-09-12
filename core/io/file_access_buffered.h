
/*  file_access_buffered.h                                               */

#ifndef FILE_ACCESS_BUFFERED_H
#define FILE_ACCESS_BUFFERED_H

#include "core/os/file_access.h"

#include "core/ustring.h"

class FileAccessBuffered : public FileAccess {
public:
	enum {
		DEFAULT_CACHE_SIZE = 128 * 1024,
	};

private:
	int cache_size = DEFAULT_CACHE_SIZE;

	int cache_data_left() const;
	mutable Error last_error;

protected:
	Error set_error(Error p_error) const;

	mutable struct File {
		bool open = false;
		int size = 0;
		int offset = 0;
		String name;
		int access_flags = 0;
	} file;

	mutable struct Cache {
		Vector<uint8_t> buffer;
		int offset = 0;
	} cache;

	virtual int read_data_block(int p_offset, int p_size, uint8_t *p_dest = nullptr) const = 0;

	void set_cache_size(int p_size);
	int get_cache_size();

public:
	virtual size_t get_position() const; ///< get position in the file
	virtual size_t get_len() const; ///< get size of the file

	virtual void seek(size_t p_position); ///< seek to a given position
	virtual void seek_end(int64_t p_position = 0); ///< seek from the end of file

	virtual bool eof_reached() const;

	virtual uint8_t get_8() const;
	virtual int get_buffer(uint8_t *p_dest, int p_length) const; ///< get an array of bytes

	virtual bool is_open() const;

	virtual Error get_error() const;

	FileAccessBuffered() {}
	virtual ~FileAccessBuffered() {}
};

#endif
