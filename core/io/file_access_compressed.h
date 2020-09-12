
/*  file_access_compressed.h                                             */

#ifndef FILE_ACCESS_COMPRESSED_H
#define FILE_ACCESS_COMPRESSED_H

#include "core/io/compression.h"
#include "core/os/file_access.h"

class FileAccessCompressed : public FileAccess {
	Compression::Mode cmode = Compression::MODE_ZSTD;
	bool writing = false;
	uint32_t write_pos = 0;
	uint8_t *write_ptr = nullptr;
	uint32_t write_buffer_size = 0;
	uint32_t write_max = 0;
	uint32_t block_size = 0;
	mutable bool read_eof = false;
	mutable bool at_end = false;

	struct ReadBlock {
		int csize;
		int offset;
	};

	mutable Vector<uint8_t> comp_buffer;
	uint8_t *read_ptr = nullptr;
	mutable int read_block = 0;
	int read_block_count = 0;
	mutable int read_block_size = 0;
	mutable int read_pos = 0;
	Vector<ReadBlock> read_blocks;
	uint32_t read_total = 0;

	String magic = "GCMP";
	mutable Vector<uint8_t> buffer;
	FileAccess *f = nullptr;

public:
	void configure(const String &p_magic, Compression::Mode p_mode = Compression::MODE_ZSTD, int p_block_size = 4096);

	Error open_after_magic(FileAccess *p_base);

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

	virtual bool file_exists(const String &p_name); ///< return true if a file exists

	virtual uint64_t _get_modified_time(const String &p_file);
	virtual uint32_t _get_unix_permissions(const String &p_file);
	virtual Error _set_unix_permissions(const String &p_file, uint32_t p_permissions);

	FileAccessCompressed() {}
	virtual ~FileAccessCompressed();
};

#endif // FILE_ACCESS_COMPRESSED_H
