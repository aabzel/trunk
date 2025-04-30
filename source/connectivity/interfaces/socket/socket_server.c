#include "socket_server.h"

#include <stdio.h>
#include <windows.h>
#include <winerror.h> //NO_ERROR
#include <winsock2.h> /*socket() WSAStartup()*/
#include <ws2tcpip.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "debug_info.h"
#include "log.h"

bool socket_server_send(uint8_t num, char* data, uint16_t size) {
    bool res = false;
    SocketHandle_t* Node = SocketGetNode(num);
    if(Node) {
        if(Node->socket_rx) {
            int stat = send(Node->socket_rx, data, size, 0);
            if(stat < 0) {
                LOG_ERROR(LG_SOCKET_SERVER, "ServerSendErr:%d", stat);
                Node->server_state = SOCKET_SERVER_IDLE;
                res = false;
                Node->socket_rx = 0;
            } else {
                LOG_INFO(LG_SOCKET_SERVER, "ServerDataSendOk,%u byte", stat);
                res = true;
            }
        } else {
            Node->socket_rx = 0;
            res = false;
            LOG_ERROR(LG_SOCKET_SERVER, "NoRxSocket");
            Node->server_state = SOCKET_SERVER_IDLE;
        }
    }
    return res;
}

bool socket_init_server(SocketHandle_t* Node) {
    bool res = false;
    int ret = 0;
    Node->server_state = SOCKET_SERVER_IDLE;
    LOG_INFO(LG_SOCKET_SERVER, "Initialising Winsock...");
    ret = WSAStartup(MAKEWORD(2, 2), &(Node->wsa));
    if(0 == ret) {
        LOG_INFO(LG_SOCKET_SERVER, "WinSockInitializationOK");

        Node->socket_server_descriptor = socket(AF_INET, SOCK_STREAM, 0);
        // Create a socket
        if(INVALID_SOCKET == Node->socket_server_descriptor) {
            res = false;
            LOG_ERROR(LG_SOCKET_SERVER, "CouldNotCreateServerSocket : %d", WSAGetLastError());
        } else {
            LOG_INFO(LG_SOCKET_SERVER, "ServerSocketCreated! %d", Node->socket_server_descriptor);

            int timeout_ms = Node->rx_timeout_ms;
            ret = setsockopt(Node->socket_server_descriptor, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout_ms,
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
                LOG_ERROR(LG_SOCKET_SERVER, "Bind failed with error code : %d", WSAGetLastError());
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
                    res = false;
                }
            }
        }
    } else {
        ret = WSAGetLastError();
        LOG_ERROR(LG_SOCKET_SERVER, "Failed.ErrorCode : %d", ret);
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

bool socket_proc_server(SocketHandle_t* Node) {
    bool res = false;
    int ret = 0;
    if(Node->socket_server_descriptor) {

        switch((uint8_t)Node->server_state) {
        case SOCKET_SERVER_IDLE: {

            struct sockaddr_in client;
            int size = 0;
            size = sizeof(struct sockaddr_in);
            LOG_PARN(LG_SOCKET_SERVER, "TryAccept...");
            Node->socket_rx = accept(Node->socket_server_descriptor, (struct sockaddr*)&client, &size);
            if(INVALID_SOCKET == Node->socket_rx) {
                ret = WSAGetLastError();
                LOG_PARN(LG_SOCKET_SERVER, "AcceptFailedWithErrorCode: %d", ret);
                Node->accept_err_cnt++;
                res = false;
            } else {
                Node->server_state = SOCKET_SERVER_CONNECTED;
                LOG_INFO(LG_SOCKET_SERVER, "ConnectionAccepted RxSocket:%d, %s,Size:%u byte", Node->socket_rx,
                         SockAddrInToStr(&client), size);
            }
        } break;
        case SOCKET_SERVER_CONNECTED: {
            LOG_PARN(LG_SOCKET_SERVER, "TryServerRx...");
            char RxData[1000] = {0};
            int ret = recv(Node->socket_rx, RxData, sizeof(RxData), 0);
            if(SOCKET_ERROR == ret) {
                LOG_PARN(LG_SOCKET_SERVER, "RxErr: %d", ret);
                Node->rx_err_cnt++;
                res = false;
            } else {
                if(ret) {
                    LOG_INFO(LG_SOCKET_SERVER, "RxOk %d", ret);
                    print_mem(RxData, ret, true, true, true, false);
                    res = true;
                }
            }
        } break;
        default:
            LOG_ERROR(LG_SOCKET_SERVER, "UndefServerState");
            break;
        }
    }
    return res;
}
