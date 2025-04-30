#include "socket_client.h"

#include <stdio.h>
#include <windows.h>
#include <winerror.h> //NO_ERROR
#include <winsock2.h> /*socket() WSAStartup()*/
#include <ws2tcpip.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "debug_info.h"
#include "log.h"

bool socket_client_send(uint8_t num, char* data, uint16_t size) {
    bool res = false;
    SocketHandle_t* Node = SocketGetNode(num);
    // int ret =0;
    if(Node) {
        int stat = send(Node->socket_client_descriptor, data, size, 0);
        if(stat < 0) {
            LOG_INFO(LG_SOCKET_CLIENT, "SendErr:%d", stat);
            res = false;
        } else {
            LOG_INFO(LG_SOCKET_CLIENT, "DataSendOk,%u byte",stat);
            res = true;
        }
    }

    return res;
}


bool socket_init_client(SocketHandle_t* Node){
    bool res = false;
    int ret = 0;
    LOG_INFO(LG_SOCKET_CLIENT, "InitialisingWinsock...");
    ret = WSAStartup(MAKEWORD(2, 2), &(Node->wsa));
    if(0 == ret) {
        LOG_INFO(LG_SOCKET_CLIENT, "WinSockInitializationOK");
        res = true;
        Node->socket_client_descriptor = socket(AF_INET, SOCK_STREAM, 0);
        if(INVALID_SOCKET == Node->socket_client_descriptor) {
            LOG_ERROR(LG_SOCKET_CLIENT, "Could not create socket : %d", WSAGetLastError());
            closesocket(Node->socket_client_descriptor);
            WSACleanup();
            res = false;
        } else { // socket_client_descriptor
            LOG_INFO(LG_SOCKET_CLIENT, "SocketCreated! %d", Node->socket_client_descriptor);

            int timeout_ms = Node->rx_timeout_ms; // Desired timeout in milliseconds
            ret = setsockopt(Node->socket_client_descriptor, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout_ms,
                             sizeof(timeout_ms));
            if(0 == ret) {
                LOG_INFO(LG_SOCKET_CLIENT, "SetSocketOptOk %d", Node->socket_client_descriptor);
            } else {
                LOG_ERROR(LG_SOCKET_CLIENT, "SetSocketOptErr Socket:%d,Ret:%d", Node->socket_client_descriptor, ret);
            }

            struct sockaddr_in server = {0};
            ZeroMemory(&server, sizeof(server));

            server.sin_family = AF_INET;
            uint32_t ip_qword = Node->server_ip.u32;
            server.sin_addr.s_addr = ip_qword; // inet_addr(ipAddrStr);  inet_addr("192.168.0.11");
            server.sin_port = htons(Node->port);

            //LOG_INFO(LG_SOCKET_CLIENT, "ip paced %08x des %08x",server.sin_addr.s_addr, tcp_server_ip);
            /* Connect to remote server */
            int con_stat = connect(Node->socket_client_descriptor, (struct sockaddr*)&server, sizeof(server));
            if(0 == con_stat) {
                LOG_INFO(LG_SOCKET_CLIENT, "Connected");
                res = true;
            } else {
                LOG_ERROR(LG_SOCKET_CLIENT, "ServerConnectError %d=0x%x", con_stat, con_stat);
                res = false;
                closesocket(Node->socket_client_descriptor);
                Node->socket_client_descriptor = 0;
                WSACleanup();
            }
        } // socket_client_descriptor
    } else {
        ret = WSAGetLastError();
        LOG_ERROR(LG_SOCKET_CLIENT, "Failed.ErrorCode : %d", ret);
        res = false;
    } //(0 == ret
    return res;
}


bool socket_proc_client(SocketHandle_t* Node ) {
    bool res = false;
    if(0 != Node->socket_client_descriptor) {
        char RxData[1000] = {0};
        int ret = recv(Node->socket_client_descriptor, RxData, sizeof(RxData), 0);
        if(SOCKET_ERROR == ret) {
            LOG_PARN(LG_SOCKET_CLIENT, "RxErr: %d", ret);
            res = false;
        } else {
            if(ret) {
                LOG_INFO(LG_SOCKET_CLIENT, "RxOk %d", ret);
                print_mem(RxData, ret, true, true, true, false);
                res = true;
            }
        }
    }

    return res;
}

bool socket_client_start(uint8_t num, uint32_t server_ip_qword,
    uint16_t port) {
    bool res = false;
    SocketHandle_t* Node = SocketGetNode(num);
    if(Node) {
        Node->role=SOCKET_ROLE_CLIENT;
        Node->server_ip.u32 = server_ip_qword;
        Node->port = port;
        Node->rx_timeout_ms = 10;
        Node->transport_ptotocol =TRANSPORT_PROTOCOL_IP_V4;
        res = socket_init_client(Node);
    }
    return res;
}
