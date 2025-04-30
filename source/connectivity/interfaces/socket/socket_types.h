#ifndef SOCKET_IF_TYPES_H
#define SOCKET_IF_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <winsock2.h>

#include "socket_const.h"
#include "data_types.h"

#define SOCKET_COMMON_VARIABLES              \
    uint8_t num;                             \
    uint16_t port;                           \
    uint32_t rx_timeout_ms;                  \
    SocketRole_t role;                       \
    Type32Union_t server_ip ;                \
    TransportPtotocol_t transport_ptotocol;  \
    bool valid;

typedef struct {
    SOCKET_COMMON_VARIABLES
}SocketConfig_t;

typedef struct {
    SOCKET_COMMON_VARIABLES
    uint32_t rx_err_cnt;
    uint32_t accept_err_cnt;
    WSADATA wsa;
    SOCKET socket_client_descriptor;
    SOCKET socket_server_descriptor;
    SOCKET socket_rx;
    ServerState_t server_state;
}SocketHandle_t;

#endif /* SOCKET_IF_TYPES_H  */
