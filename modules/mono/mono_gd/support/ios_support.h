
/*  ios_support.h                                                        */



#ifndef IOS_SUPPORT_H
#define IOS_SUPPORT_H

#if defined(IPHONE_ENABLED)

#include "core/ustring.h"

namespace gdmono {
namespace ios {
namespace support {

void initialize();
void cleanup();

} // namespace support
} // namespace ios
} // namespace gdmono

#endif // IPHONE_ENABLED

#endif // IOS_SUPPORT_H
