#ifndef SOCKET_IF_CONST_H
#define SOCKET_IF_CONST_H


#include "socket_dep.h"

#define  SOCKET_PERIOD_US (10)

typedef enum{
    SOCKET_ROLE_SERVER=1,
    SOCKET_ROLE_CLIENT=2,

    SOCKET_ROLE_UNDEF=0,
}SocketRole_t;


typedef enum{
    SOCKET_SERVER_IDLE=1,
    SOCKET_SERVER_CONNECTED=2,

    SOCKET_SERVER_UNDEF=0,
}ServerState_t;


typedef enum{
    TRANSPORT_PROTOCOL_UDP=1,
    TRANSPORT_PROTOCOL_IP_V4=2,

    TRANSPORT_PROTOCOL_UNDEF=0,
}TransportPtotocol_t;

#endif /* SOCKET_IF_CONST_H  */
