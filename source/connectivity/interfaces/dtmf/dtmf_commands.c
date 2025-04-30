#include "dtmf_commands.h"

#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "dtmf_diag.h"
#include "dtmf_drv.h"
#include "log.h"

bool dtmf_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = dtmf_diag();
    return res;
}

bool dtmf_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t data[100];
    size_t tx_size = 0;
    uint32_t duration_ms = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &tx_size);
        if(false == res) {
            strncpy(data, argv[1], sizeof(data));
            tx_size = strlen(argv[1]);
            res = true;
        }
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &duration_ms);
    }

    if(res) {
        res = dtmf_send(num, data, tx_size, duration_ms);
        if(res) {
            LOG_INFO(DTMF, "TxOk");
        }
    } else {
        LOG_ERROR(DTMF, "Usage dts Num Data Duratuin");
    }
    return res;
}

bool dtmf_send_char_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t duration_ms = 0;
    char letter = '?';

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        letter = argv[1][0];
        res = true;
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &duration_ms);
    }

    if(res) {
        res = dtmf_send_char(num, letter, duration_ms);
        if(res) {
            LOG_INFO(DTMF, "TxOk");
        }
    } else {
        LOG_ERROR(DTMF, "Usage dtc Num Letter Duration_ms");
    }
    return res;
}

bool dtmf_calc_period_command(int32_t argc, char* argv[]) {
    bool res = false;
    char letter = '?';
    uint32_t seed = 0;

    if(1 <= argc) {
        letter = argv[0][0];
        res = true;
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &seed);
    }

    if(res) {
        uint32_t N = 0;
        uint32_t M = 0;
        res = dtmf_calc_periods(seed, letter, &N, &M);
        if(res) {
            LOG_INFO(DTMF, "%c N:%u M:%u", letter, N, M);
        }
    } else {
        LOG_ERROR(DTMF, "Usage dtp Letter seed");
    }

    return res;
}
