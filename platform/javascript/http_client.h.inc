
/*  http_client.h.inc                                                    */

// HTTPClient's additional private members in the javascript platform

Error prepare_request(Method p_method, const String &p_url, const Vector<String> &p_headers);

int xhr_id;
int read_limit = 4096;
int response_read_offset = 0;
Status status = STATUS_DISCONNECTED;

String host;
int port = -1;
bool use_tls = false;
String username;
String password;

int polled_response_code = 0;
String polled_response_header;
PackedByteArray polled_response;

#ifdef DEBUG_ENABLED
bool has_polled = false;
uint64_t last_polling_frame = 0;
#endif
