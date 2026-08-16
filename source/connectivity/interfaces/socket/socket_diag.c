#include "socket_diag.h"

#include <stdio.h>
#include <winsock2.h>

#include "csv.h"
#include "log.h"
#include "convert.h"
#include "socket_if.h"

static char cText[150] = "";

const char *MacToStr (uint8_t *mac_addr) {
    static char lText[100] = "";
    snprintf ((char *)lText, sizeof (lText), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1],
              mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    return lText;
}


const char *IpToStr(uint8_t *ip_addr) {
    static char lText[100] = "";
    snprintf ((char *)lText, sizeof (lText), "%02d.%02d.%02d.%02d",
            ip_addr[0],
            ip_addr[1],
            ip_addr[2],
              ip_addr[3]);
    return lText;
}

const char * SocketRoleToStr(SocketRole_t role) {
    const char * name = "?";
    switch(role){
    case SOCKET_ROLE_SERVER: name = "Server";break;
    case SOCKET_ROLE_CLIENT: name = "Client";break;
    default: break;
    }
    return name;
}

const char * TransportToStr(TransportPtotocol_t transport_ptotocol) {
    const char * name = "?";
    switch(transport_ptotocol){
        case TRANSPORT_PROTOCOL_IP_V4: name = "IP_V4";break;
        case TRANSPORT_PROTOCOL_UDP: name = "UDP";break;
        default: break;
    }
    return name;
}

const char * SocketServerStateToStr(ServerState_t state) {
    const char * name = "?";
    switch(state){
        case SOCKET_SERVER_IDLE: name = "Idle";break;
        case SOCKET_SERVER_CONNECTED: name = "Connected";break;
        default: break;
    }
    return name;
}


/*
https://learn.microsoft.com/ru-ru/windows/win32/winsock/windows-sockets-error-codes-2
*/
const char * WSAErrorToStr(const int err_code) {
    const char * name = "?";
    switch(err_code){
#if 0
        case WSA_INVALID_HANDLE: name = "WSA_INVALID_HANDLE";break;
        case WSA_NOT_ENOUGH_MEMORY: name = "WSA_NOT_ENOUGH_MEMORY";break;
        case WSA_INVALID_PARAMETER: name = "WSA_INVALID_PARAMETER";break;
        case WSA_OPERATION_ABORTED: name = "WSA_OPERATION_ABORTED";break;
        case WSA_IO_INCOMPLETE: name = "WSA_IO_INCOMPLETE";break;
        case WSA_IO_PENDING: name = "WSA_IO_PENDING";break;
#endif
        case WSAEINTR: name = "WSAEINTR";break;
        case WSAEBADF: name = "WSAEBADF";break;
        case WSAEACCES: name = "WSAEACCES";break;
        case WSAEFAULT: name = "WSAEFAULT";break;
        case WSAEINVAL: name = "WSAEINVAL";break;
        case WSAEMFILE: name = "WSAEMFILE";break;
        case WSAEWOULDBLOCK: name = "WSAEWOULDBLOCK";break;
        case WSAEINPROGRESS: name = "WSAEINPROGRESS";break;
        case WSAEALREADY: name = "WSAEALREADY";break;
        case WSAENOTSOCK: name = "WSAENOTSOCK";break;
        case WSAEDESTADDRREQ: name = "WSAEDESTADDRREQ";break;
        case WSAEMSGSIZE: name = "WSAEMSGSIZE";break;
        case WSAEPROTOTYPE: name = "WSAEPROTOTYPE";break;
        case WSAENOPROTOOPT: name = "WSAENOPROTOOPT";break;
        case WSAEPROTONOSUPPORT: name = "WSAEPROTONOSUPPORT";break;
        case WSAESOCKTNOSUPPORT: name = "WSAESOCKTNOSUPPORT";break;
        case WSAEOPNOTSUPP: name = "WSAEOPNOTSUPP";break;
        case WSAEPFNOSUPPORT: name = "WSAEPFNOSUPPORT";break;
        case WSAEAFNOSUPPORT: name = "WSAEAFNOSUPPORT";break;
        case WSAEADDRINUSE: name = "WSAEADDRINUSE";break;
        case WSAEADDRNOTAVAIL: name = "WSAEADDRNOTAVAIL";break;
        case WSAENETDOWN: name = "WSAENETDOWN";break;
        case WSAENETUNREACH: name = "WSAENETUNREACH";break;
        case WSAENETRESET: name = "WSAENETRESET";break;
        case WSAECONNABORTED: name = "WSAECONNABORTED";break;
        case WSAECONNRESET: name = "WSAECONNRESET";break;
        case WSAENOBUFS: name = "WSAENOBUFS";break;
        case WSAEISCONN: name = "WSAEISCONN";break;
        case WSAENOTCONN: name = "WSAENOTCONN";break;
        default:
        name = "?";
         break;
    }
    return name;
}



const char* SocketConfigToStr(SocketConfig_t* Config){
    static char in_text[200] = "?";
    snprintf(in_text, sizeof(in_text), "No:%u,Role:%s,IP:%s,Port:%u,RxTimeOut:%u ms,Transport:%s",
            Config->num,
            SocketRoleToStr(Config->role),
            IpToStr(Config->server_ip.u8),
            Config->port ,
            Config->rx_timeout_ms ,
            TransportToStr(Config->transport_ptotocol)
            );
    return in_text;
}




#if 0
bool parse_mac (char *inStr, uint16_t inStrLen, uint8_t *outMacAddr) {
    bool res = false;
    if (strlen ("MAC") < inStrLen) {
        char *serialStartPtr = strstr (inStr, "MAC ");
        if (NULL != serialStartPtr) {
            res = try_str2mac ((const char *)(serialStartPtr + strlen ("MAC ")), outMacAddr);
        } else {
            printf ("\n lack MAC addr in [%s]", inStr);
        }
    }
    return res;
}
#endif

static bool is_ip_number (char letter) {
    bool res = false;
    switch (letter) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            res = true;
            break;
        default: break;
    }
    return res;
}

uint16_t calc_ip_val_len(char *inStr) {
    uint16_t strValLen = 0;
    if (inStr) {
        bool runLoop = true;
        while (runLoop) {
            if (is_ip_number (inStr[strValLen])) {
                strValLen++;
            } else {
                runLoop = false;
            }
        }
    }
    return strValLen;
}

#if 0
bool parse_ip (char *inStr, uint16_t inStrLen, uint32_t *outIpAddr) {
    bool res = false;
    if (strlen ("IP ") < inStrLen) {
        char *serialStartPtr = strstr (inStr, "IP ");
        if (NULL != serialStartPtr) {
            uint32_t IpLen;
            IpLen = calc_ip_val_len ((serialStartPtr + strlen ("IP ")));
            res = try_strl2ipv4 ((const char *)(serialStartPtr + strlen ("IP ")), IpLen, outIpAddr);
        } else {
            printf ("\n lack IP addr in [%s]", inStr);
        }
    }
    return res;
}
#endif


const char * SockAddrInToStr(struct sockaddr_in* client) {
    static char in_text[200] = "?";
    snprintf(in_text, sizeof(in_text), "Port:%u,Addr:%u.%u.%u.%u,SinFamily:%u",
            client->sin_port,
            client->sin_addr.S_un.S_un_b.s_b1,
            client->sin_addr.S_un.S_un_b.s_b2,
            client->sin_addr.S_un.S_un_b.s_b3,
            client->sin_addr.S_un.S_un_b.s_b4,
            client->sin_family
            );
    return in_text;
}


bool try_str2ip_v4(const char    * const in_text, uint8_t* const ip_array){
    bool res = false;
    if(in_text){
        if(ip_array){
            uint32_t cnt=csv_cnt(in_text, '.');
            if(4==cnt){
                char temp[4*3]={0};
                uint32_t i = 0 ;
                uint32_t ok = 0 ;
                for(i=0; i<4; i++){
                    memset(temp,0,sizeof(temp));
                    res = csv_parse_text(in_text, '.', i, temp, sizeof(temp));
                    if(res) {
                        res = try_str2uint8(temp, &ip_array[i]);
                        if(res) {
                            ok++;
                        } else {
                            LOG_ERROR(LG_SOCKET,"%u,NotU8Err [%s]",i,temp);
                        }
                    }
                }
                if(4==ok){
                    res = true;
                }else{
                   res = false;
                }
            }else {
                LOG_ERROR(LG_SOCKET,"CntErr:%u",cnt);
            }
        }
    }
    return res;
}


const char* SocketNodeToStr(const SocketHandle_t* const Node) {
    strcpy(cText, "");
    if(Node) {
        snprintf(cText, sizeof(cText), "%sN:%u,", cText, Node->num);
        snprintf(cText, sizeof(cText), "%s[%s],", cText, Node->name);
        snprintf(cText, sizeof(cText), "%sPort:%u,", cText, Node->port);
        snprintf(cText, sizeof(cText), "%sFrame:%s,", cText, SocketRoleToStr(Node->role));
        snprintf(cText, sizeof(cText), "%sProt:%s,", cText, TransportToStr(Node->transport_ptotocol));
        snprintf(cText, sizeof(cText), "%sState:%s,", cText, SocketServerStateToStr(Node->server_state));
        snprintf(cText, sizeof(cText), "%sRxTO:%u ms,", cText, Node->rx_timeout_ms);
        snprintf(cText, sizeof(cText), "%sSerIP:0x%08x,", cText, Node->server_ip.u32);
    }
    return cText;
}
