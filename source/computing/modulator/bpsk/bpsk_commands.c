#include "bpsk_commands.h"

#include <stdio.h>
#include <string.h>

#include "bpsk.h"
#include "convert.h"
#include "log.h"

bool bpsk_decode_wav_command(int32_t argc, char* argv[]){
    bool res = false ;
    uint8_t num = 1;
    uint32_t bit_rate = 16;
    char file_name[300]="";
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(BPSK, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(2<=argc) {
        res = strcpy(file_name, argv[1]);
    }


    if(3<=argc) {
        res = try_str2uint32(argv[2], &bit_rate);
        BpskHandle_t* Node=BpskGetNode(num);
        if(Node) {
            Node->bit_rate = bit_rate;
        }
    }

    if(res) {
        res = bpsk_decode_wav(num, file_name);
        res = log_res(BPSK,  res, "Decode,Wav");
    }else{
        LOG_ERROR(BPSK, "Usage: bpskdw Num FileName");
    }

    return res;
}

bool bpsk_diag_command(int32_t argc, char* argv[]){
    bool res = false ;
    return res;
}

/*
 bpskew 1 0x55aa
 bpskew 1 0x5555 100 3
 */
bool bpsk_encode_to_wav_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t array[256]={0};
    uint32_t repetition = 1;
    size_t size = 0;
    uint32_t bit_rate = 100;

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(BPSK, "Arg1 NumErr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], array, sizeof(array), &size);
        if(false == res) {
            LOG_WARNING(BPSK, "ExtractHexArrayErr [%s]", argv[1]);
            snprintf((char*)array, sizeof(array), "[%s]", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }else{
        }
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &bit_rate);
        if(res) {
            BpskHandle_t* Node=BpskGetNode(num);
            if(Node) {
                Node->bit_rate = bit_rate;
            }
        }
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &repetition);
        if(false == res) {
            LOG_ERROR(BPSK, "Arg1 RepErr %s", argv[3]);
        }
    }

    if(res) {
    	res = bpsk_reinit_node(num);
        res = bpsk_encode_to_wav(num, array, size, repetition);
        res = log_res(BPSK, res, "Encode,To,Wav");
    }else{
        LOG_ERROR(BPSK, "Usage: bpskew Num HexData Baud repetition");
    }
    return res;
}
