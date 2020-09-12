
/*  http_request.h                                                       */

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

typedef enum {
	XHR_READY_STATE_UNSENT = 0,
	XHR_READY_STATE_OPENED = 1,
	XHR_READY_STATE_HEADERS_RECEIVED = 2,
	XHR_READY_STATE_LOADING = 3,
	XHR_READY_STATE_DONE = 4,
} godot_xhr_ready_state_t;

extern int godot_xhr_new();
extern void godot_xhr_reset(int p_xhr_id);
extern bool godot_xhr_free(int p_xhr_id);

extern int godot_xhr_open(int p_xhr_id, const char *p_method, const char *p_url, const char *p_user = nullptr, const char *p_password = nullptr);

extern void godot_xhr_set_request_header(int p_xhr_id, const char *p_header, const char *p_value);

extern void godot_xhr_send_null(int p_xhr_id);
extern void godot_xhr_send_string(int p_xhr_id, const char *p_data);
extern void godot_xhr_send_data(int p_xhr_id, const void *p_data, int p_len);
extern void godot_xhr_abort(int p_xhr_id);

/* this is an HTTPClient::ResponseCode, not ::Status */
extern int godot_xhr_get_status(int p_xhr_id);
extern godot_xhr_ready_state_t godot_xhr_get_ready_state(int p_xhr_id);

extern int godot_xhr_get_response_headers_length(int p_xhr_id);
extern void godot_xhr_get_response_headers(int p_xhr_id, char *r_dst, int p_len);

extern int godot_xhr_get_response_length(int p_xhr_id);
extern void godot_xhr_get_response(int p_xhr_id, void *r_dst, int p_len);

#ifdef __cplusplus
}
#endif

#endif /* HTTP_REQUEST_H */
