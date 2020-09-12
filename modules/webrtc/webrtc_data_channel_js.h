
/*  webrtc_data_channel_js.h                                             */

#ifdef JAVASCRIPT_ENABLED

#ifndef WEBRTC_DATA_CHANNEL_JS_H
#define WEBRTC_DATA_CHANNEL_JS_H

#include "webrtc_data_channel.h"

class WebRTCDataChannelJS : public WebRTCDataChannel {
	GDCLASS(WebRTCDataChannelJS, WebRTCDataChannel);

private:
	String _label;
	String _protocol;

	bool _was_string;
	WriteMode _write_mode;

	enum {
		PACKET_BUFFER_SIZE = 65536 - 5 // 4 bytes for the size, 1 for for type
	};

	int _js_id;
	RingBuffer<uint8_t> in_buffer;
	int queue_count;
	uint8_t packet_buffer[PACKET_BUFFER_SIZE];

public:
	void _on_open();
	void _on_close();
	void _on_error();
	void _on_message(uint8_t *p_data, uint32_t p_size, bool p_is_string);

	virtual void set_write_mode(WriteMode mode) override;
	virtual WriteMode get_write_mode() const override;
	virtual bool was_string_packet() const override;

	virtual ChannelState get_ready_state() const override;
	virtual String get_label() const override;
	virtual bool is_ordered() const override;
	virtual int get_id() const override;
	virtual int get_max_packet_life_time() const override;
	virtual int get_max_retransmits() const override;
	virtual String get_protocol() const override;
	virtual bool is_negotiated() const override;

	virtual Error poll() override;
	virtual void close() override;

	/** Inherited from PacketPeer: **/
	virtual int get_available_packet_count() const override;
	virtual Error get_packet(const uint8_t **r_buffer, int &r_buffer_size) override; ///< buffer is GONE after next get_packet
	virtual Error put_packet(const uint8_t *p_buffer, int p_buffer_size) override;

	virtual int get_max_packet_size() const override;

	WebRTCDataChannelJS();
	WebRTCDataChannelJS(int js_id);
	~WebRTCDataChannelJS();
};

#endif // WEBRTC_DATA_CHANNEL_JS_H

#endif // JAVASCRIPT_ENABLED
