
/*  compression.h                                                        */

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "core/typedefs.h"

class Compression {
public:
	static int zlib_level;
	static int gzip_level;
	static int zstd_level;
	static bool zstd_long_distance_matching;
	static int zstd_window_log_size;

	enum Mode {
		MODE_FASTLZ,
		MODE_DEFLATE,
		MODE_ZSTD,
		MODE_GZIP
	};

	static int compress(uint8_t *p_dst, const uint8_t *p_src, int p_src_size, Mode p_mode = MODE_ZSTD);
	static int get_max_compressed_buffer_size(int p_src_size, Mode p_mode = MODE_ZSTD);
	static int decompress(uint8_t *p_dst, int p_dst_max_size, const uint8_t *p_src, int p_src_size, Mode p_mode = MODE_ZSTD);

	Compression() {}
};

#endif // COMPRESSION_H
