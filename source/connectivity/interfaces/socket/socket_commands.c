#include "socket_commands.h"

#include <stddef.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "socket_if.h"


bool socket_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    if(1<=argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_SOCKET, "ParseErr Num [1....8]");
        }
    }
    return res;
}

bool socket_init_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    if(1<=argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_SOCKET, "ParseErr Num [1....8]");
        }
    }

    if(res) {
        res=socket_init_one(num);
        if(res){
        	LOG_INFO(LG_SOCKET, "InitOk");
        } else {
        	LOG_ERROR(LG_SOCKET, "InitErr");
        }
    }

    return res;
}

bool socket_server_send_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t array[256];
    size_t array_len = 0;
    uint8_t num = 0;
    if(1<=argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_SOCKET, "ParseErr Num");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], array, sizeof(array), &array_len);
        if(false == res) {
            LOG_WARNING(LG_SOCKET, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)array, sizeof(array), "%s", argv[1]);
            array_len = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = socket_server_send(  num , array, array_len) ;
        if(res){
        	LOG_INFO(LG_SOCKET, "ServerSendOk");
        } else {
        	LOG_ERROR(LG_SOCKET, "ServerSendErr");
        }
    }else{
    	LOG_ERROR(LG_SOCKET, "Usage: sss Num Data");
    }
	return res;
}


bool socket_client_send_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t array[256];
    size_t array_len = 0;
    uint8_t num = 0;
    if(1<=argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_SOCKET, "ParseErr Num");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], array, sizeof(array), &array_len);
        if(false == res) {
            LOG_WARNING(LG_SOCKET, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)array, sizeof(array), "%s", argv[1]);
            array_len = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = socket_client_send(  num , array,   array_len) ;
        if(res){
        	LOG_INFO(LG_SOCKET, "SendOk");
        } else {
        	LOG_ERROR(LG_SOCKET, "SendErr");
        }
    }
	return res;
}


bool socket_server_start_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    uint16_t port = 0;
    if(1<=argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_SOCKET, "ParseErr Num");
        }
    }

    if(2<=argc) {
        res = try_str2uint16(argv[1], &port);
        if(false == res) {
            LOG_ERROR(LG_SOCKET, "ParseErr Port");
        }
    }

    if(res) {
       res=socket_server_start(num,port);
       if(res) {
       	LOG_INFO(LG_SOCKET_SERVER, "StartOk");
       } else {
       	LOG_ERROR(LG_SOCKET_SERVER, "StartErr");
       }
    }

    return res;
}

bool socket_client_start_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    uint16_t port = 0;
    Type32Union_t server_ip;
    server_ip.u32 = 0;
    if(1<=argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_SOCKET_CLIENT, "ParseErr Num");
        }
    }

    if(2<=argc) {
        res = try_str2ip_v4(argv[1], &server_ip.u8[0]);
        if(false == res) {
            LOG_ERROR(LG_SOCKET_CLIENT, "ParseErr IP");
        }
    }

    if(3<=argc) {
        res = try_str2uint16(argv[1], &port);
        if(false == res) {
            LOG_ERROR(LG_SOCKET_CLIENT, "ParseErr Port");
        }
    }

    if(res) {
       res = socket_client_start(num, server_ip.u32, port);
       if(res) {
           LOG_INFO(LG_SOCKET_CLIENT, "StartOk");
       } else {
           LOG_ERROR(LG_SOCKET_CLIENT, "StartErr");
       }
    }
    return res;
}

