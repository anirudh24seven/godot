
/*  copymem.h                                                            */



#ifndef COPYMEM_H
#define COPYMEM_H

#include "core/typedefs.h"

#ifdef PLATFORM_COPYMEM

#include "platform_copymem.h" // included from platform/<current_platform>/platform_copymem.h"

#else

#include <string.h>

#define copymem(to, from, count) memcpy(to, from, count)
#define zeromem(to, count) memset(to, 0, count)
#define movemem(to, from, count) memmove(to, from, count)

#endif

#endif // COPYMEM_H
