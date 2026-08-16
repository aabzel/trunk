#include "socket_server.h"

#include <stdio.h>
#include <windows.h>
#include <winerror.h> //NO_ERROR
#include <winsock2.h> /*socket() WSAStartup()*/
#include <ws2tcpip.h>

#include "socket_if.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "array_diag.h"
#include "debug_info.h"
#include "log.h"
#include "can_shell_mcal.h"

#ifdef HAS_ISO_TP
#include "iso_tp_mcal.h"
#endif

bool socket_server_send(uint8_t num, char* data, uint16_t size) {
    bool res = false;
    SocketHandle_t* Node = SocketGetNode(num);
    if(Node) {
        if(Node->socket_remote) {
            int stat = send(Node->socket_remote, data, size, 0);
            if(stat < 0) {
                LOG_ERROR(LG_SOCKET_SERVER, "ServerSendErr:%d", stat);
                Node->server_state = SOCKET_SERVER_IDLE;
                res = false;
                Node->socket_remote = 0;
            } else {
                LOG_INFO(LG_SOCKET_SERVER, "ServerDataSendOk,%u byte", stat);
                res = true;
            }
        } else {
            Node->socket_remote = 0;
            res = false;
            LOG_ERROR(LG_SOCKET_SERVER, "NoRxSocket");
            Node->server_state = SOCKET_SERVER_IDLE;
        }
    }
    return res;
}

bool socket_init_server(SocketHandle_t * const Node) {
    bool res = false;
    int ret = 0;
    Node->server_state = SOCKET_SERVER_IDLE;
    LOG_INFO(LG_SOCKET_SERVER, "InitialisingWinsock...");
    ret = WSAStartup(MAKEWORD(2, 2), &(Node->wsa));
    if(0 == ret) {
        LOG_INFO(LG_SOCKET_SERVER, "WinSockInitializationOK");

        Node->socket_server_descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP );
        // Create a socket
        if(INVALID_SOCKET == Node->socket_server_descriptor) {
            res = false;
            ret = WSAGetLastError();
            LOG_ERROR(LG_SOCKET_SERVER, "CouldNotCreateServerSocket,ErrCode:%d=%s", ret,WSAErrorToStr(ret));
            WSACleanup();
        } else {
            LOG_INFO(LG_SOCKET_SERVER, "SocketCreated:Desc:%d", Node->socket_server_descriptor);

            int timeout_ms = Node->rx_timeout_ms;
            ret = setsockopt(Node->socket_server_descriptor, SOL_SOCKET, SO_RCVTIMEO,
                            (char*)&timeout_ms,
                             sizeof(timeout_ms));
            if(0 == ret) {
                LOG_INFO(LG_SOCKET_SERVER, "SetSocketOptOk %d", Node->socket_server_descriptor);
            } else {
                LOG_ERROR(LG_SOCKET_SERVER, "SetSocketOptErr Socket:%d,Ret:%d", Node->socket_server_descriptor, ret);
            }

            struct sockaddr_in server = {0};
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(Node->port);

            ret = bind(Node->socket_server_descriptor, (struct sockaddr*)&server, sizeof(server));
            if(SOCKET_ERROR == ret) {
                res = false;
                int err_code = WSAGetLastError();
                LOG_ERROR(LG_SOCKET_SERVER, "BindFailedWithErrorCode:ErrCode:%d=%s", err_code,WSAErrorToStr(err_code));
                closesocket(Node->socket_server_descriptor);
                WSACleanup();
            } else {
                LOG_INFO(LG_SOCKET_SERVER, "BindDone");

                // Listen to incoming connections
                ret = listen(Node->socket_server_descriptor, 3);
                if(0 == ret) {
                    LOG_INFO(LG_SOCKET_SERVER, "Waiting for incoming connections...");

                    u_long NonBlock = 1;
                    ret = ioctlsocket(Node->socket_server_descriptor, FIONBIO, &NonBlock);
                    if(SOCKET_ERROR == ret) {
                        LOG_ERROR(LG_SOCKET_SERVER, "Setting non blocking failed");
                        res = false;
                    } else {
                        res = true;
                        LOG_INFO(LG_SOCKET_SERVER, "Setting non blocking Ok");
                    }

                } else {
                    LOG_ERROR(LG_SOCKET_SERVER, "ListenErr %d", ret);
                    closesocket(Node->socket_server_descriptor);
                    WSACleanup();
                    res = false;
                }
            }
        }
    } else {
        ret = WSAGetLastError();
        LOG_ERROR(LG_SOCKET_SERVER, "Failed:ErrCode:%d=%s", ret,WSAErrorToStr(ret));
        res = false;
    } //(0 == ret
    return res;
}

bool socket_server_start(uint8_t num, uint16_t port) {
    bool res = false;
    SocketHandle_t* Node = SocketGetNode(num);
    if(Node) {
        Node->port = port;
        Node->rx_timeout_ms = 10;
        Node->role = SOCKET_ROLE_SERVER;
        Node->server_ip.u32 = 0;
        Node->transport_ptotocol = TRANSPORT_PROTOCOL_IP_V4;
        res = socket_init_server(Node);
    }
    return res;
}

static bool socket_server_proc_idle(SocketHandle_t * const Node) {
    bool res = false;
    struct sockaddr_in client;
    int size = 0;
    size = sizeof(struct sockaddr_in);
    LOG_PARN(LG_SOCKET_SERVER, "TryAccept...");
    Node->socket_remote = accept(Node->socket_server_descriptor, (struct sockaddr*) &client, &size);
    if (INVALID_SOCKET == Node->socket_remote) {
        int ret = 0;
        ret = WSAGetLastError();
        LOG_PARN(LG_SOCKET_SERVER, "AcceptFailedWithErrorCode,ErrCode:%d=%s", ret,WSAErrorToStr(ret));
        Node->accept_err_cnt++;
        res = false;
    } else {
        Node->server_state = SOCKET_SERVER_CONNECTED;
        LOG_INFO(LG_SOCKET_SERVER, "ConnectionAccepted RxSocket:%d, %s,Size:%u byte", Node->socket_remote,
                SockAddrInToStr(&client), size);
    }
    return res;
}

static bool socket_server_connected_tx_proc(SocketHandle_t *const Node) {
    bool res = false;
    uint32_t tx_len = fifo_get_count(&Node->TxFifo );
    if(tx_len) {
        uint8_t TxPart[150] = {0};
        uint32_t tx_size = 0 ;
        res= fifo_pull_array(&Node->TxFifo , TxPart, sizeof(TxPart), &tx_size);
        if(res) {
            int tx_done_cnt = send(Node->socket_remote, (char*) TxPart, (int) tx_size, 0 );
            if(tx_done_cnt==tx_size) {
                res = true;
            } else {
                res = false ;
                int ret = 0;
                ret = WSAGetLastError();
                LOG_ERROR(LG_SOCKET_SERVER, "SendFailedWithErrorCode,ErrCode:%d=%s", ret,WSAErrorToStr(ret));
            }
        }
    }
    return res;
}

static bool socket_server_connected_rx_proc(SocketHandle_t *const Node){
    bool res = false;
    LOG_PARN(LG_SOCKET_SERVER, "TryServerRx,[%s]",SocketNodeToStr(Node));
    char RxData[1000] = { 0 };
    int rx_cnt = recv(Node->socket_remote, RxData, sizeof(RxData), 0);
    if (SOCKET_ERROR == rx_cnt) {
        LOG_PARN(LG_SOCKET_SERVER, "RxErr: %d", rx_cnt);
        Node->rx_err_cnt++;
        res = false;
    } else {
        if (0 < rx_cnt) {
            res = true;
            LOG_PARN(LG_SOCKET_SERVER, "Rx,[%s]",SocketNodeToStr(Node));
            print_mem((uint8_t*) RxData, rx_cnt, true, true, true, false);
            CanShellHandle_t *CanShell = CanShellGetNode(1);
            if (CanShell) {
                if(Node->port==CanShell->socket_port) {
                    LOG_INFO(LG_SOCKET_SERVER, "Rx:%d,[%s]", rx_cnt,ArrayToAsciiStr((uint8_t*) RxData,rx_cnt));
                    res = iso_tp_send(CanShell->iso_tp_num, CanShell->iso_tp_target_address, (uint8_t*) RxData, rx_cnt);
                }
            }
        }
    }
    return res;
}

static bool socket_server_proc_connected(SocketHandle_t *const Node) {
    bool res = false;
    res = socket_server_connected_rx_proc(Node);
    res = socket_server_connected_tx_proc(Node) && res;
    return res;
}

bool socket_proc_server(SocketHandle_t* const Node) {
    bool res = false;
    if(Node->socket_server_descriptor) {
        switch(Node->server_state) {
        case SOCKET_SERVER_IDLE: {
            res = socket_server_proc_idle(Node);
        } break;
        case SOCKET_SERVER_CONNECTED: {
            res = socket_server_proc_connected(Node) ;
        } break;
        default:
            LOG_ERROR(LG_SOCKET_SERVER, "UndefServerState");
            break;
        }
    }
    return res;
}
