#ifndef SOCKET_DIAG_H
#define SOCKET_DIAG_H

#include "socket_types.h"

const char * SockAddrInToStr(struct sockaddr_in* client) ;
const char* SocketNodeToStr(SocketHandle_t* Node);
const char* SocketConfigToStr(SocketConfig_t* Config);
const char* IpToStr(uint8_t *ip_addr);
const char* MacToStr(uint8_t *mac_addr);
bool try_str2ip_v4(const char const  *text, uint8_t* const ip_array);


#endif /* SOCKET_DIAG_H  */
