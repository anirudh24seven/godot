
/*  pck_packer.h                                                         */

#ifndef PCK_PACKER_H
#define PCK_PACKER_H

#include "core/reference.h"

class FileAccess;

class PCKPacker : public Reference {
	GDCLASS(PCKPacker, Reference);

	FileAccess *file = nullptr;
	int alignment;
	uint64_t ofs = 0;

	Vector<uint8_t> key;
	bool enc_dir = false;

	static void _bind_methods();

	struct File {
		String path;
		String src_path;
		uint64_t ofs;
		uint64_t size;
		bool encrypted;
		Vector<uint8_t> md5;
	};
	Vector<File> files;

public:
	Error pck_start(const String &p_file, int p_alignment = 0, const String &p_key = String(), bool p_encrypt_directory = false);
	Error add_file(const String &p_file, const String &p_src, bool p_encrypt = false);
	Error flush(bool p_verbose = false);

	PCKPacker() {}
	~PCKPacker();
};

#endif // PCK_PACKER_H
