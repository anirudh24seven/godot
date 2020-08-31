
/*  path_utils.h                                                         */



#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include "core/string_builder.h"
#include "core/ustring.h"

namespace path {

String join(const String &p_a, const String &p_b);
String join(const String &p_a, const String &p_b, const String &p_c);
String join(const String &p_a, const String &p_b, const String &p_c, const String &p_d);

/// Returns a normalized absolute path to the current working directory
String cwd();

/**
 * Obtains a normalized absolute path to p_path. Symbolic links are
 * not resolved. The path p_path might not exist in the file system.
 */
String abspath(const String &p_path);

/**
 * Obtains a normalized path to p_path with symbolic links resolved.
 * The resulting path might be either a relative or an absolute path.
 */
String realpath(const String &p_path);

String relative_to(const String &p_path, const String &p_relative_to);

} // namespace path

#endif // PATH_UTILS_H
