#include "socket_config.h"

#include "data_utils.h"
#include "common_const.h"
#include "socket_const.h"

const SocketConfig_t SocketConfig[] = {
    {.num=1, .port=65432, .rx_timeout_ms=10, .role = SOCKET_ROLE_CLIENT, .server_ip.u8={192,168,3,36}, .valid=true, .transport_ptotocol=TRANSPORT_PROTOCOL_IP_V4,},
    {.num=2, .port=64555, .rx_timeout_ms=10, .role = SOCKET_ROLE_SERVER, .server_ip.u8={192,168,3,36}, .valid=true, .transport_ptotocol=TRANSPORT_PROTOCOL_IP_V4,},
    {.num=3, .port=0, .rx_timeout_ms=10, .role = SOCKET_ROLE_UNDEF, .server_ip.u8={0,0,0,0}, .valid=true, .transport_ptotocol=TRANSPORT_PROTOCOL_UNDEF,},
    {.num=4, .port=0, .rx_timeout_ms=10, .role = SOCKET_ROLE_UNDEF, .server_ip.u8={0,0,0,0}, .valid=true, .transport_ptotocol=TRANSPORT_PROTOCOL_UNDEF,},
};

SocketHandle_t SocketInstance[]={
    {.num=1, .valid=true,},
    {.num=2, .valid=true,},
    {.num=3, .valid=true,},
    {.num=4, .valid=true,},
};


COMPONENT_GET_CNT(Socket, socket)
