
/*  class_db_api_json.h                                                  */

#ifndef CLASS_DB_API_JSON_H
#define CLASS_DB_API_JSON_H

// 'core/method_bind.h' defines DEBUG_METHODS_ENABLED, but it looks like we
// cannot include it here. That's why we include it through 'core/class_db.h'.
#include "core/class_db.h"

#ifdef DEBUG_METHODS_ENABLED

#include "core/ustring.h"

void class_db_api_to_json(const String &p_output_file, ClassDB::APIType p_api);

#endif // DEBUG_METHODS_ENABLED

#endif // CLASS_DB_API_JSON_H
