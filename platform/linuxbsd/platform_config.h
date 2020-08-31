
/*  platform_config.h                                                    */



#ifdef __linux__
#include <alloca.h>
#endif
#if defined(__FreeBSD__) || defined(__OpenBSD__)
#include <stdlib.h>
#define PTHREAD_BSD_SET_NAME
#endif
