#ifndef SOCKET_DIAG_H
#define SOCKET_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "socket_types.h"

const char* SocketNodeToStr(const SocketHandle_t *const Node);
const char* SocketServerStateToStr(ServerState_t state);
const char* SocketRoleToStr(SocketRole_t role);
const char* TransportToStr(TransportPtotocol_t transport_ptotocol);
const char* SockAddrInToStr(struct sockaddr_in *client);
const char* WSAErrorToStr(const int err_code);
const char* SocketConfigToStr(SocketConfig_t *Config);
const char* IpToStr(uint8_t *ip_addr);
const char* MacToStr(uint8_t *mac_addr);
bool try_str2ip_v4(const char *const text, uint8_t *const ip_array);
uint16_t calc_ip_val_len(char *inStr);

#ifdef __cplusplus
}
#endif


#endif /* SOCKET_DIAG_H  */
