#ifndef SOCKET_IF_CONST_H
#define SOCKET_IF_CONST_H


#include "socket_dep.h"

#define  SOCKET_PERIOD_US (10)

typedef enum{
    SOCKET_ROLE_SERVER,
    SOCKET_ROLE_CLIENT,

    SOCKET_ROLE_UNDEF,
}SocketRole_t;


typedef enum{
    SOCKET_SERVER_CONNECTED,
    SOCKET_SERVER_IDLE,

    SOCKET_SERVER_UNDEF,
}ServerState_t;


typedef enum{
    TRANSPORT_PROTOCOL_IP_V4,
    TRANSPORT_PROTOCOL_UDP,

    TRANSPORT_PROTOCOL_UNDEF,
}TransportPtotocol_t;

#endif /* SOCKET_IF_CONST_H  */
