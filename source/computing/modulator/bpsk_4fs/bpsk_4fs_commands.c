#include "bpsk_4fs_commands.h"

#include <stdio.h>
#include <string.h>

#include "bpsk_4fs_mcal.h"
#include "convert.h"
#include "log.h"
#include "bpsk_4fs_diag.h"

#ifdef HAS_WAV
bool bpsk_4fs_decode_wav_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t bit_rate = 16;
    char file_name[300]="";
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(BPSK_4FS, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(2<=argc) {
        res = strcpy(file_name, argv[1]);
    }

    if(3<=argc) {
        res = try_str2uint32(argv[2], &bit_rate);
        Bpsk4fsHandle_t* Node=Bpsk4fsGetNode(num);
        if(Node) {
            Node->bit_rate = bit_rate;
        }
    }

    if(res) {
        res = bpsk_4fs_decode_wav(num, file_name);
        res = log_res(BPSK_4FS, res, "Decode,Wav");
    } else {
        LOG_ERROR(BPSK_4FS, "Usage: bpsk_4fsdw Num FileName");
    }

    return res;
}
#endif

bool bpsk_4fs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if (0 <= argc) {
        res = true;
        num = 1;
    }

    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if (res) {
        res = bpsk_4fs_diag(num);
    }
    return res;
}

#ifdef HAS_WAV
/*
 bpsk_4fsew 1 0x55aa
 bpsk_4fsew 1 0x5555 100 3
 */
bool bpsk_4fs_encode_to_wav_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t array[256]= {0};
    uint32_t repetition = 1;
    size_t size = 0;
    uint32_t bit_rate = 100;

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(BPSK_4FS, "Arg1 NumErr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], array, sizeof(array), &size);
        if(false == res) {
            LOG_WARNING(BPSK_4FS, "ExtractHexArrayErr [%s]", argv[1]);
            snprintf((char*)array, sizeof(array), "[%s]", argv[1]);
            size = strlen(argv[1]);
            res = true;
        } else {
        }
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &bit_rate);
        if(res) {
            Bpsk4fsHandle_t* Node=Bpsk4fsGetNode(num);
            if(Node) {
                Node->bit_rate = bit_rate;
            }
        }
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &repetition);
        if(false == res) {
            LOG_ERROR(BPSK_4FS, "Arg1 RepErr %s", argv[3]);
        }
    }

    if(res) {
        res = bpsk_4fs_reinit_node(num);
        res = bpsk_4fs_encode_to_wav(num, array, size, repetition);
        res = log_res(BPSK_4FS, res, "Encode,To,Wav");
    } else {
        LOG_ERROR(BPSK_4FS, "Usage: bpsk_4fsew Num HexData Baud repetition");
    }
    return res;
}
#endif

/*
brbp 1 1
*/
bool bpsk_4fs_rx_bit_phase_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    int32_t rx_bit_phase = 0;
    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if (2 <= argc) {
        res = try_str2int32(argv[1], &rx_bit_phase);
    }

    if (res) {
        res = bpsk_4fs_rx_bit_phase(num, rx_bit_phase);
    } else {
        LOG_ERROR(BPSK_4FS, "Usage: brbp Num RxBitPhase");
    }

    return res;
}
