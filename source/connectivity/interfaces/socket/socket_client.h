#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <stdbool.h>
#include <stdint.h>

#include "socket_config.h"
#include "socket_types.h"
#ifdef HAS_SOCKET_DIAG
#include "socket_diag.h"
#endif

bool socket_init_client(SocketHandle_t* Node);
bool socket_proc_client(SocketHandle_t* Node ) ;
bool socket_client_send(uint8_t num, char* data, uint16_t size);
bool socket_client_start(uint8_t num, uint32_t server_ip_qword, uint16_t port);


#endif /* SOCKET_CLIENT_H  */
