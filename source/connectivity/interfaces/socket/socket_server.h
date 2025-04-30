#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <stdbool.h>
#include <stdint.h>

#include "socket_config.h"
#include "socket_types.h"
#ifdef HAS_SOCKET_DIAG
#include "socket_diag.h"
#endif

bool socket_server_start(uint8_t num, uint16_t port);
bool socket_init_server(SocketHandle_t* Node);
bool socket_server_send(uint8_t num, char* data, uint16_t size);
bool socket_proc_server(SocketHandle_t* Node);

#endif /* SOCKET_SERVER_H  */
