
/*  upnp_device.h                                                        */

#ifndef GODOT_UPNP_DEVICE_H
#define GODOT_UPNP_DEVICE_H

#include "core/reference.h"

class UPNPDevice : public Reference {
	GDCLASS(UPNPDevice, Reference);

public:
	enum IGDStatus {

		IGD_STATUS_OK,
		IGD_STATUS_HTTP_ERROR,
		IGD_STATUS_HTTP_EMPTY,
		IGD_STATUS_NO_URLS,
		IGD_STATUS_NO_IGD,
		IGD_STATUS_DISCONNECTED,
		IGD_STATUS_UNKNOWN_DEVICE,
		IGD_STATUS_INVALID_CONTROL,
		IGD_STATUS_MALLOC_ERROR,
		IGD_STATUS_UNKNOWN_ERROR,
	};

	void set_description_url(const String &url);
	String get_description_url() const;

	void set_service_type(const String &type);
	String get_service_type() const;

	void set_igd_control_url(const String &url);
	String get_igd_control_url() const;

	void set_igd_service_type(const String &type);
	String get_igd_service_type() const;

	void set_igd_our_addr(const String &addr);
	String get_igd_our_addr() const;

	void set_igd_status(IGDStatus status);
	IGDStatus get_igd_status() const;

	bool is_valid_gateway() const;
	String query_external_address() const;
	int add_port_mapping(int port, int port_internal = 0, String desc = "", String proto = "UDP", int duration = 0) const;
	int delete_port_mapping(int port, String proto = "UDP") const;

	UPNPDevice();
	~UPNPDevice();

protected:
	static void _bind_methods();

private:
	String description_url;
	String service_type;
	String igd_control_url;
	String igd_service_type;
	String igd_our_addr;
	IGDStatus igd_status;
};

VARIANT_ENUM_CAST(UPNPDevice::IGDStatus)

#endif // GODOT_UPNP_DEVICE_H
