#include "file_pc_commands.h"
#define _XOPEN_SOURCE_EXTENDED 1
#include <stdio.h>
#include <stdlib.h> // for realpath
#include <limits.h>

#include "convert.h"
#include "file_pc.h"
#include "array_diag.h"
#include "log.h"



static FILE* FileNode=NULL;

bool file_pc_load_to_array_i8_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t offset = 0 ;
    uint32_t size = 0 ;
    int8_t out_buff[200]={0};
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &offset);
        if(false == res) {
            LOG_ERROR(FILE_PC, "ParseErr offset");
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        if(false == res) {
            LOG_ERROR(FILE_PC, "ParseErr size");
        }
    }

    if(res) {
        if(FileNode) {
            res = file_pc_load_to_array_i8_ll(FileNode, (size_t) offset, out_buff, (size_t) size);
            if(res){
                res= array_i8_print(out_buff, size);
                cli_printf(CRLF);
            }else{
                LOG_ERROR(FILE_PC, "LoadErr");
            }
        }else{
            LOG_ERROR(FILE_PC, "FilePrtErr");
        }
    }else{
        LOG_ERROR(FILE_PC, "Usage: fplai8 offset size");
    }
    return res;
}


bool file_pc_open_command(int32_t argc, char* argv[]){
    bool res = false;
    if(1<=argc){
        res = true;
    }

    if(res){
        FileNode = fopen(argv[0], "r");
        if(FileNode){
            LOG_INFO(FILE_PC, "OpenOk");
        }else{
            LOG_ERROR(FILE_PC, "OpenErr");
            res = false ;
        }
    }
    return res;
}

bool file_pc_close_command(int32_t argc, char* argv[]){
    bool res = false;

    if(FileNode) {
        fclose(FileNode);
        res = true;
    }

    return res;
}


//realpath - return the canonicalized absolute pathname
bool file_pc_realpath_command(int32_t argc, char* argv[]){
    bool res = false;
    char out_path[300]={0};
    res = file_pc_realpath(argv[0], out_path);
    res = log_res(FILE_PC, res, "RealPath");
    if(res) {
        LOG_INFO(FILE_PC, "OutPath:[%s]",out_path);
    }

    return res;
}
