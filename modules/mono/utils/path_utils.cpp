
/*  path_utils.cpp                                                       */



#include "path_utils.h"

#include "core/os/dir_access.h"
#include "core/os/file_access.h"
#include "core/os/os.h"
#include "core/project_settings.h"

#ifdef WINDOWS_ENABLED
#include <windows.h>

#define ENV_PATH_SEP ";"
#else
#include <limits.h>
#include <unistd.h>

#define ENV_PATH_SEP ":"
#endif

#include <stdlib.h>

namespace path {

String cwd() {
#ifdef WINDOWS_ENABLED
	const DWORD expected_size = ::GetCurrentDirectoryW(0, nullptr);

	String buffer;
	buffer.resize((int)expected_size);
	if (::GetCurrentDirectoryW(expected_size, buffer.ptrw()) == 0)
		return ".";

	return buffer.simplify_path();
#else
	char buffer[PATH_MAX];
	if (::getcwd(buffer, sizeof(buffer)) == nullptr) {
		return ".";
	}

	String result;
	if (result.parse_utf8(buffer)) {
		return ".";
	}

	return result.simplify_path();
#endif
}

String abspath(const String &p_path) {
	if (p_path.is_abs_path()) {
		return p_path.simplify_path();
	} else {
		return path::join(path::cwd(), p_path).simplify_path();
	}
}

String realpath(const String &p_path) {
#ifdef WINDOWS_ENABLED
	// Open file without read/write access
	HANDLE hFile = ::CreateFileW(p_path.c_str(), 0,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
		return p_path;

	const DWORD expected_size = ::GetFinalPathNameByHandleW(hFile, nullptr, 0, FILE_NAME_NORMALIZED);

	if (expected_size == 0) {
		::CloseHandle(hFile);
		return p_path;
	}

	String buffer;
	buffer.resize((int)expected_size);
	::GetFinalPathNameByHandleW(hFile, buffer.ptrw(), expected_size, FILE_NAME_NORMALIZED);

	::CloseHandle(hFile);
	return buffer.simplify_path();
#elif UNIX_ENABLED
	char *resolved_path = ::realpath(p_path.utf8().get_data(), nullptr);

	if (!resolved_path) {
		return p_path;
	}

	String result;
	bool parse_ok = result.parse_utf8(resolved_path);
	::free(resolved_path);

	if (parse_ok) {
		return p_path;
	}

	return result.simplify_path();
#endif
}

String join(const String &p_a, const String &p_b) {
	if (p_a.empty()) {
		return p_b;
	}

	const CharType a_last = p_a[p_a.length() - 1];
	if ((a_last == '/' || a_last == '\\') ||
			(p_b.size() > 0 && (p_b[0] == '/' || p_b[0] == '\\'))) {
		return p_a + p_b;
	}

	return p_a + "/" + p_b;
}

String join(const String &p_a, const String &p_b, const String &p_c) {
	return path::join(path::join(p_a, p_b), p_c);
}

String join(const String &p_a, const String &p_b, const String &p_c, const String &p_d) {
	return path::join(path::join(path::join(p_a, p_b), p_c), p_d);
}

String relative_to_impl(const String &p_path, const String &p_relative_to) {
	// This function assumes arguments are normalized and absolute paths

	if (p_path.begins_with(p_relative_to)) {
		return p_path.substr(p_relative_to.length() + 1);
	} else {
		String base_dir = p_relative_to.get_base_dir();

		if (base_dir.length() <= 2 && (base_dir.empty() || base_dir.ends_with(":"))) {
			return p_path;
		}

		return String("..").plus_file(relative_to_impl(p_path, base_dir));
	}
}

#ifdef WINDOWS_ENABLED
String get_drive_letter(const String &p_norm_path) {
	int idx = p_norm_path.find(":/");
	if (idx != -1 && idx < p_norm_path.find("/"))
		return p_norm_path.substr(0, idx + 1);
	return String();
}
#endif

String relative_to(const String &p_path, const String &p_relative_to) {
	String relative_to_abs_norm = abspath(p_relative_to);
	String path_abs_norm = abspath(p_path);

#ifdef WINDOWS_ENABLED
	if (get_drive_letter(relative_to_abs_norm) != get_drive_letter(path_abs_norm)) {
		return path_abs_norm;
	}
#endif

	return relative_to_impl(path_abs_norm, relative_to_abs_norm);
}

} // namespace path
