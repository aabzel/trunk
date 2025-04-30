#include "socket_diag.h"

#include <stdio.h>

#include "csv.h"
#include "log.h"
#include "socket_if.h"

const char* SocketNodeToStr(SocketHandle_t* Node){
    static char text[20] = "?";

    return text;
}

const char *MacToStr (uint8_t *mac_addr) {
    static char name[100] = "";
    snprintf ((char *)name, sizeof (name), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1],
              mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    return name;
}


const char *IpToStr(uint8_t *ip_addr) {
    static char name[100] = "";
    snprintf ((char *)name, sizeof (name), "%02d.%02d.%02d.%02d",
            ip_addr[0],
            ip_addr[1],
            ip_addr[2],
              ip_addr[3]);
    return name;
}

const char * SocketRoleToStr(SocketRole_t role){
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


const char* SocketConfigToStr(SocketConfig_t* Config){
    static char text[200] = "?";
    snprintf(text, sizeof(text), "No:%u,Role:%s,IP:%s,Port:%u,RxTimeOut:%u ms,Transport:%s",
            Config->num,
            SocketRoleToStr(Config->role),
            IpToStr(Config->server_ip.u8),
            Config->port ,
            Config->rx_timeout_ms ,
            TransportToStr(Config->transport_ptotocol)
            );
    return text;
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
    static char text[200] = "?";
    snprintf(text, sizeof(text), "Port:%u,Addr:%u.%u.%u.%u,SinFamily:%u",
            client->sin_port,
            client->sin_addr.S_un.S_un_b.s_b1,
            client->sin_addr.S_un.S_un_b.s_b2,
            client->sin_addr.S_un.S_un_b.s_b3,
            client->sin_addr.S_un.S_un_b.s_b4,
            client->sin_family
            );
    return text;
}


bool try_str2ip_v4(const char const  *text, uint8_t* const ip_array){
    bool res = false;
    if(text){
        if(ip_array){
            uint32_t cnt=csv_cnt(text, '.');
            if(4==cnt){
                char temp[4*3]={0};
                uint32_t i = 0 ;
                uint32_t ok = 0 ;
                for(i=0; i<4; i++){
                    memset(temp,0,sizeof(temp));
                    res=csv_parse_text(text, '.', i, temp, sizeof(temp));
                    if(res){
                        res=try_str2uint8(temp, &ip_array[i]);
                        if(res) {
                            ok++;
                        } else {
                            LOG_ERROR(LINE,"%u,NotU8Err [%s]",i,temp);
                        }
                    }
                }
                if(4==ok){
                    res = true;
                }else{
                   res = false;
                }
            }else {
                LOG_ERROR(LINE,"CntErr:%u",cnt);
            }
        }
    }
    return res;
}

