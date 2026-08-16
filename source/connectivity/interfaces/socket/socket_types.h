#ifndef SOCKET_IF_TYPES_H
#define SOCKET_IF_TYPES_H

#include <winsock2.h>

#include "std_includes.h"
#include "socket_const.h"
#include "data_types.h"
#include "fifo_char_types.h"

#define SOCKET_COMMON_VARIABLES              \
    uint8_t* TxFifoMem;                      \
    uint32_t tx_fifo_mem_size;               \
    uint8_t num;                             \
    char* name;                              \
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
    FifoChar_t TxFifo;
    uint32_t accept_err_cnt;
    WSADATA wsa;
    SOCKET socket_client_descriptor;
    SOCKET socket_server_descriptor;
    SOCKET socket_remote;
    ServerState_t server_state;
}SocketHandle_t;

#endif /* SOCKET_IF_TYPES_H  */
