#include "decadriver_commands.h"

#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "debug_info.h"
#include "decadriver.h"
#include "decadriver_config.h"
#include "decadriver_diag.h"
#include "log.h"
#include "time_mcal.h"

bool decadriver_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(DECA, "argc %u ", argc);
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = decadriver_init();
        if(res) {
            LOG_INFO(DECA, "Init" LOG_OK);
        } else {
            LOG_ERROR(DECA, "Init" LOG_ER);
        }
    }
    return res;
}

bool decadriver_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    set_log_level(DECA, LOG_LEVEL_INFO);
    LOG_INFO(DECA, "argc %u ", argc);
    if(0 == argc) {
        res = true;
    }

    res = decadriver_diag(&DecaDriverInstance);
    // set_log_level(DECA, LOG_LEVEL_ERROR);
    return res;
}

bool decadriver_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        dwt_rxreset();
    } else {
        LOG_ERROR(DECA, "Usage: dwr");
    }
    return res;
}

bool decadriver_read_offset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_file = 0;
    uint8_t offset = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &reg_file);
        if(false == res) {
            LOG_ERROR(DECA, "ParseErr RegFile");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &offset);
        if(false == res) {
            LOG_ERROR(DECA, "ParseErr offset");
        }
    }

    if(res) {
        uint32 val = dwt_read32bitoffsetreg((int)reg_file, (int)offset);
        LOG_INFO(DECA, "RegFile 0x%02x offset:%u Val 0x%08x", reg_file, offset, val);
    } else {
        LOG_ERROR(DECA, "Usage: dro regFile offset");
    }
    return res;
}

static bool decadriver_parse_reg_and_offset(int32_t argc, char* argv[], int* out_reg_file, int* out_reg_offset) {
    bool res = false;
    int reg_file = 0;
    int reg_offset = 0;

    if(0 == argc) {
        res = false;
    }

    if(1 <= argc) {
        res = try_str2int32(argv[0], (int32_t*)&reg_file);
        if(false == res) {
            LOG_ERROR(DECA, "ParseErr RegFile");
        } else {
            *out_reg_file = reg_file;
        }
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], (int32_t*)&reg_offset);
        if(false == res) {
            LOG_ERROR(DECA, "ParseErr RegOffSet");
        } else {
            *out_reg_offset = reg_offset;
        }
    }

    return res;
}

bool decadriver_read_register_one_command(int32_t argc, char* argv[]) {
    bool res = false;
    int reg_file = 0;
    int reg_offset = 0;
    uint32 reg_val = 0;

    res = decadriver_parse_reg_and_offset(argc, argv, &reg_file, &reg_offset);

    if(res) {
        switch(argc) {
        case 1: {
            reg_val = dwt_read32bitreg(reg_file);
        } break;

        case 2: {
            reg_val = dwt_read32bitoffsetreg(reg_file, reg_offset);
        } break;
        } // switch
        LOG_INFO(DECA, "Reg 0x%x[0x%x]=0x%08x", reg_file, reg_offset, reg_val);
    }

    return res;
}

bool decadriver_write_reg32_command(int32_t argc, char* argv[]) {
    bool res = false;
    int reg_file = 0;
    int reg_offset = 0;
    uint32_t reg_val = 0;

    res = decadriver_parse_reg_and_offset(argc, argv, &reg_file, &reg_offset);

    if(3 <= argc) {
        res = try_str2uint32(argv[2], (uint32_t*)&reg_val);
        if(false == res) {
            LOG_ERROR(DECA, "ParseErr RegVal");
        }
    }

    if(res) {
        if(3 == argc) {
            dwt_write32bitoffsetreg(reg_file, reg_offset, reg_val);
        }
    }

    return res;
}

bool decadriver_write_tx_buff_command(int32_t argc, char* argv[]) {
    bool res = false;
    size_t tx_size = 0;
    if(1 <= argc) {
        res = try_str2array(argv[0], DecaDriverInstance.buff, sizeof(DecaDriverInstance.buff), &tx_size);
        if(false == res) {
            LOG_WARNING(DECA, "ExtractHexArrayErr  [%s]", argv[0]);
            snprintf((char*)DecaDriverInstance.buff, sizeof(DecaDriverInstance.buff), "%s", argv[0]);
            tx_size = strlen(argv[0]);
            res = true;
        }
    }

    if(res) {
        LOG_INFO(DECA, "Write: [%u] byte", tx_size);
        int ret = dwt_writetxdata(tx_size, DecaDriverInstance.buff, 0);
        if(DWT_SUCCESS == ret) {
            res = true;
        } else {
            res = false;
        }
    } else {
        LOG_ERROR(DECA, "Usage: dwtxb HexArray");
    }
    return res;
}

bool decadriver_tx_command(int32_t argc, char* argv[]) {
    bool res = false;
    size_t tx_size = 0;
    if(1 <= argc) {
        res = try_str2array(argv[0], DecaDriverInstance.buff, sizeof(DecaDriverInstance.buff), &tx_size);
        if(false == res) {
            LOG_WARNING(DECA, "ExtractHexArrayErr  [%s]", argv[0]);
            snprintf((char*)DecaDriverInstance.buff, sizeof(DecaDriverInstance.buff), "%s", argv[0]);
            tx_size = strlen(argv[0]);
            res = true;
        }
    }

    if(res) {
        LOG_DEBUG(DECA, "TryTx: [%u] byte", tx_size);
        res = decadriver_tx(DecaDriverInstance.buff, tx_size + 2);
        if(res) {
            LOG_INFO(DECA, "TxOk");
        } else {
            LOG_ERROR(DECA, "TxErr");
        }
    } else {
        LOG_ERROR(DECA, "Usage: dtb HexArray");
    }
    return res;
}

bool decadriver_read_rx_buff_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t size = 0;
    if(0 == argc) {
        res = true;
        size = RX_BUF_LEN - 1;
    }

    if(1 <= argc) {
        res = try_str2uint16(argv[0], &size);
        if(false == res) {
            LOG_ERROR(DECA, "ParseErr size");
        }
    }

    if(res) {
        dwt_readrxdata(DecaDriverInstance.buff, size, 0);
        if(res) {
            print_hex(DecaDriverInstance.buff, size);
        }
    } else {
        LOG_ERROR(DECA, "Usage drrb size");
    }
    return res;
}

bool decadriver_rx_set_command(int32_t argc, char* argv[]) {
    bool res = false;

    int mode = -1;
    if(0 <= argc) {
        res = true;
        mode = DWT_START_RX_IMMEDIATE;
    }

    if(1 <= argc) {
        res = try_str2int32(argv[0], (int32_t*)&mode);
        if(false == res) {
            LOG_ERROR(DECA, "ParseModeErr");
        }
    }

    if(res) {
        int ret = -1;
        ret = dwt_rxenable(mode);
        if(DWT_SUCCESS == ret) {
            LOG_INFO(DECA, "RxSetOk");
        } else {
            LOG_ERROR(DECA, "RxSetErr");
        }

    } else {
        LOG_ERROR(DECA, "Usage drs");
    }
    return res;
}

bool decadriver_rx_reset_command(int32_t argc, char* argv[]) {
    bool res = true;
    dwt_rxreset();
    LOG_INFO(DECA, "RxReset");
    return res;
}
