#include "socket_if.h"

#include <stdio.h>
#include <windows.h>
#include <winerror.h> //NO_ERROR
#include <winsock2.h> /*socket() WSAStartup()*/
#include <ws2tcpip.h>

/**
 *
 *   https://www.binarytides.com/winsock-socket-programming-tutorial/
     https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
 */

#include "byte_utils.h"
#include "code_generator.h"
#include "debug_info.h"
#include "log.h"

COMPONENT_GET_NODE(Socket, socket)

COMPONENT_GET_CONFIG(Socket, socket)

bool socket_init_one(uint8_t num) {
    bool res = false;
    const SocketConfig_t* Config = SocketGetConfig(num);
    if(Config) {
        LOG_WARNING(LG_SOCKET, "%s", SocketConfigToStr(Config));
        SocketHandle_t* Node = SocketGetNode(num);
        if(Node) {
            LOG_WARNING(LG_SOCKET, "Init:%d", num);
            Node->port = Config->port;
            Node->role = Config->role;
            Node->rx_timeout_ms = Config->rx_timeout_ms;
            Node->server_ip.u32 = Config->server_ip.u32;
            Node->transport_ptotocol = Config->transport_ptotocol;
            Node->valid = true;
            Node->socket_client_descriptor = 0;

            switch((uint8_t)Config->role) {
            case SOCKET_ROLE_CLIENT:
                res = socket_init_client(Node);
                break;
            case SOCKET_ROLE_SERVER:
                res = socket_init_server(Node);
                break;
            default:
                LOG_PARN(LG_SOCKET, "NoRoleErr");
                break;
            }

        } // Node
    }     // Config
    return res;
}

bool socket_init_custom(void) {
    bool res = true;
    log_level_get_set(LG_SOCKET, LOG_LEVEL_DEBUG);
    return res;
}

bool socket_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(LG_SOCKET, "Proc:%u", num);
    SocketHandle_t* Node = SocketGetNode(num);
    if(Node) {

        switch((uint8_t)Node->role) {
        case SOCKET_ROLE_CLIENT:
            res = socket_proc_client(Node);
            break;
        case SOCKET_ROLE_SERVER:
            res = socket_proc_server(Node);
            break;
        default:
            LOG_PARN(LG_SOCKET, "NoRoleErr");
            break;
        }
    }

    return res;
}

COMPONENT_PROC_PATTERT(LG_SOCKET, SOCKET, socket)

COMPONENT_INIT_PATTERT(LG_SOCKET, SOCKET, socket)
