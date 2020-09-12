
/*  register_types.cpp                                                   */

#include "register_types.h"

#include "crypto_mbedtls.h"
#include "dtls_server_mbedtls.h"
#include "packet_peer_mbed_dtls.h"
#include "stream_peer_mbedtls.h"

void register_mbedtls_types() {
	CryptoMbedTLS::initialize_crypto();
	StreamPeerMbedTLS::initialize_ssl();
	PacketPeerMbedDTLS::initialize_dtls();
	DTLSServerMbedTLS::initialize();
}

void unregister_mbedtls_types() {
	DTLSServerMbedTLS::finalize();
	PacketPeerMbedDTLS::finalize_dtls();
	StreamPeerMbedTLS::finalize_ssl();
	CryptoMbedTLS::finalize_crypto();
}
