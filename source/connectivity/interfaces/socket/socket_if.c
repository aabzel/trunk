#include "socket_if.h"

#include <stdio.h>
#include <windows.h>
#include <winerror.h> //NO_ERROR
#include <winsock2.h> /*socket() WSAStartup()*/
#include <ws2tcpip.h>

/*
     https://www.binarytides.com/winsock-socket-programming-tutorial/
     https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
 */

#include "byte_utils.h"
#include "code_generator.h"
#include "debug_info.h"
#include "log.h"

COMPONENT_GET_NODE(Socket, socket)

COMPONENT_GET_CONFIG(Socket, socket)

static bool socket_init_common(const SocketConfig_t* const Config, SocketHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->port = Config->port;
            Node->role = Config->role;
            Node->rx_timeout_ms = Config->rx_timeout_ms;
            Node->server_ip.u32 = Config->server_ip.u32;
            Node->transport_ptotocol = Config->transport_ptotocol;
            res = true;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
static bool SocketIsValidConfig(const SocketConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(LG_SOCKET, "%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->port) {
            LOG_ERROR(LG_SOCKET, "%u,port,Err", Config->num);
            res = false;
        }

        ifn(Config->role) {
            LOG_ERROR(LG_SOCKET, "%u,role,Err", Config->num);
            res = false;
        }

        ifn(Config->transport_ptotocol) {
            LOG_ERROR(LG_SOCKET, "%u,transportPtotocol,Err", Config->num);
            res = false;
        }

        ifn(Config->TxFifoMem) {
            LOG_ERROR(LG_SOCKET, "%u,TxFifoMem,Err", Config->num);
            res = false;
        }

        ifn(Config->tx_fifo_mem_size) {
            LOG_ERROR(LG_SOCKET, "%u,tx_fifo_mem_size,Err", Config->num);
            res = false;
        }
    }
    return res;
}


static bool socket_init_node(const SocketConfig_t* const Config, SocketHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->valid = true;
            res = fifo_init(&Node->TxFifo, Config->TxFifoMem, Config->tx_fifo_mem_size);
            log_debug_res(LG_SOCKET, res, "TxFifoInit");

            switch(Config->role) {
                case SOCKET_ROLE_CLIENT:
#ifdef HAS_SOCKET_CLIENT
                    res = socket_init_client(Node);
#endif
                    break;
                case SOCKET_ROLE_SERVER:
#ifdef HAS_SOCKET_SERVER
                    res = socket_init_server(Node);
#endif
                    break;
                default:
                    res = false;
                    LOG_ERROR(LG_SOCKET, "NoRoleErr");
                    break;
            }
            Node->socket_client_descriptor = 0;
            res = true;
        }
    }
    return res;
}

bool socket_init_one(uint8_t num) {
    bool res = false;
    const SocketConfig_t* Config = SocketGetConfig(num);
    res=SocketIsValidConfig(Config);
    if(res) {
        res = false;
        LOG_WARNING(LG_SOCKET, "%s", SocketConfigToStr(Config));
        SocketHandle_t* Node = SocketGetNode(num);
        if(Node) {
            LOG_WARNING(LG_SOCKET, "Init:%d", num);
            res = socket_init_common(Config, Node) ;
            res = socket_init_node(Config, Node) ;
        }
    }
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

        switch(Node->role) {
        case SOCKET_ROLE_CLIENT:
#ifdef HAS_SOCKET_CLIENT
            res = socket_proc_client(Node);
#endif
            break;
        case SOCKET_ROLE_SERVER:
#ifdef HAS_SOCKET_SERVER
            res = socket_proc_server(Node);
#endif
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
