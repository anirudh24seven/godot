
/*  websocket_macros.h                                                   */



#ifndef WEBSOCKETMACTOS_H
#define WEBSOCKETMACTOS_H

// Defaults per peer buffers, 1024 packets with a shared 65536 bytes payload.
#define DEF_PKT_SHIFT 10
#define DEF_BUF_SHIFT 16

/* clang-format off */
#define GDCICLASS(CNAME) \
public:\
	static CNAME *(*_create)();\
\
	static Ref<CNAME > create_ref() {\
\
		if (!_create)\
			return Ref<CNAME >();\
		return Ref<CNAME >(_create());\
	}\
\
	static CNAME *create() {\
\
		if (!_create)\
			return nullptr;\
		return _create();\
	}\
protected:\

#define GDCINULL(CNAME) \
CNAME *(*CNAME::_create)() = nullptr;

#define GDCIIMPL(IMPNAME, CNAME) \
public:\
	static CNAME *_create() { return memnew(IMPNAME); }\
	static void make_default() { CNAME::_create = IMPNAME::_create; }\
protected:\
/* clang-format on */

#endif // WEBSOCKETMACTOS_H
