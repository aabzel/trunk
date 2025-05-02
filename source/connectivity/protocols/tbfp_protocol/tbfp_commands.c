#include "tbfp_commands.h"

#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "interfaces_diag.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "std_includes.h"
#include "system.h"
#include "system_diag.h"
#include "tbfp.h"
#include "tbfp_retx_diag.h"
#include "writer_generic.h"

bool tbfp_storage_erase_generate_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = tbfp_storage_erase_generate();
    log_info_res(TBFP, res, "GenErase");
    return res;
}

/*
   tgj 0x80000000
 */
bool tbfp_generate_jump_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t base_address = 0x80000000;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &base_address);
        log_info_res(TBFP, res, "Addr");
    }

    if(res) {
        res = tbfp_generate_jump(base_address);
        log_info_res(TBFP, res, "GenJump");
    } else {
        LOG_ERROR(TBFP, "Usage: tgj addr");
    }
    return res;
}

bool tbfp_storage_write_generate_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint16_t size = 0;
    uint8_t pattern = 0;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        log_info_res(TBFP, res, "Addr");
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &size);
        log_info_res(TBFP, res, "Size");
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &pattern);
        log_info_res(TBFP, res, "Pattern");
    }

    if(res) {
        res = tbfp_storage_write_generate(address, size, pattern);
    } else {
        LOG_ERROR(TBFP, "Usage: tswg addr size pattern");
    }
    return res;
}

bool tbfp_storage_read_generate_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t address = 0;
    uint16_t size = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        log_info_res(TBFP, res, "Addr");
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &size);
        log_info_res(TBFP, res, "Size");
    }

    if(res) {
        res = tbfp_storage_read_generate(address, size);
    } else {
        LOG_ERROR(TBFP, "Usage: tsrg addr size");
    }
    return res;
}

bool tbfp_diag_retx_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = false;
#if HAS_TBFP_RETRANSMIT
        res = tbfp_diag_retx();
        log_info_res(TBFP, res, "DiagReTx");
#endif
    }
    return res;
}

bool tbfp_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t interface = IF_UNDEF;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &interface);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr if %s", argv[0]);
        }
    }

#ifdef HAS_TBFP_DIAG
    if(2 <= argc) {
        TbfpHandle_t* TbfpNode = TbfpInterfaceToNode(interface);
        if(TbfpNode) {
            res = try_str2bool(argv[1], &TbfpNode->debug);
            if(false == res) {
                LOG_ERROR(SYS, "ParseErr state %s", argv[1]);
            }
        }
    }
#endif
    if(2 < argc) {
        LOG_ERROR(TBFP, "Usage: tbfpd if debug");
    }
    if(res) {
        res = false;
#ifdef HAS_TBFP_DIAG
        res = tbfp_diag();
        log_info_res(TBFP, res, "Diag");
#endif
    }
    return res;
}

bool tbfp_error_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(res) {
#ifdef HAS_TBFP_DIAG
        res = tbfp_error();
        log_info_res(TBFP, res, "Err");
#endif
    } else {
        LOG_ERROR(TBFP, "Usage: tbfpd if debug");
    }

    return res;
}

bool tbfp_rate_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(res) {
#ifdef HAS_TBFP_DIAG
        res = tbfp_rate_diago();
        log_info_res(TBFP, res, "Diag");
#endif
    } else {
        LOG_ERROR(TBFP, "Usage: tbt");
    }
    return res;
}

bool tbfp_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t array[256] = {0};
    uint32_t array_len = 0;
    uint8_t livetime = 0;
    uint8_t ack = 0;
    uint8_t interface = IF_UNDEF;
    if(1 <= argc) {
        res = try_str2array(argv[0], array, sizeof(array), &array_len);
        if(false == res) {
            LOG_ERROR(TBFP, "ParseErr data %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &interface);
        if(false == res) {
            LOG_ERROR(TBFP, "UnableToParseInterface");
        }
    }
    if(3 <= argc) {
        res = try_str2uint8(argv[2], &livetime);
        if(false == res) {
            LOG_ERROR(TBFP, "UnableToParseLivetime");
        }
    }
    if(4 <= argc) {
        res = try_str2uint8(argv[3], &ack);
        if(false == res) {
            LOG_ERROR(TBFP, "UnableToParseAck");
        }
    }

    if(res) {
        res = tbfp_send_payload(array, array_len, (Interfaces_t)interface, livetime, (TbfpAck_t)ack, FRAME_ID_UNDEF);
        log_info_res(TBFP, res, "Tx");
    } else {
        LOG_ERROR(TBFP, "Usage: tbfpds data interface");
    }
    return res;
}

bool tbfp_send_hi_load_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t attempt = 0;
    uint32_t len = 0;
    uint32_t pause_ms = 0;
    uint8_t interface = IF_UNDEF;
    uint8_t array[255 - TBFP_OVERHEAD_SIZE] = {0};
    memset(array, 0, len);

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &len);
        if(false == res) {
            LOG_ERROR(TBFP, "UnableToParseLen");
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &attempt);
        if(false == res) {
            LOG_ERROR(TBFP, "UnableToParseAtt");
        }
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &pause_ms);
        if(false == res) {
            LOG_ERROR(TBFP, "UnableToParsePause");
        }
    }

    if(4 <= argc) {
        res = try_str2uint8(argv[3], &interface);
        if(false == res) {
            LOG_ERROR(TBFP, "UnableToParseInterface");
        }
    }

    if(4 != argc) {
        LOG_ERROR(TBFP, "Usage: tbfsh"
                        " len"
                        " attempt"
                        " pause_ms"
                        " interf");
        return res;
    }

    if(res) {
        if(len <= sizeof(array)) {
            uint32_t i = 0;
            for(i = 0; i < attempt; i++) {
                memset(array, ((uint8_t)i), len);
                res = tbfp_send_payload(array, len, (Interfaces_t)interface, 0, ACK_NO_NEED, FRAME_ID_UNDEF);
                log_info_res(TBFP, res, "Tx");
                wait_in_loop_ms(pause_ms);
            }
        }
    }
    return res;
}

bool tbfp_send_ping_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t frame_id = FRAME_ID_PING;
    Interfaces_t interface = IF_LOOPBACK;

    if(0 == argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &interface);
        log_info_res(TBFP, res, "ParseIf");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &frame_id);
        log_info_res(TBFP, res, "ParseFrameId");
    }

    if(res) {
#ifdef HAS_INTERFACES_DIAG
        LOG_ERROR(TBFP, "IF:%s,FR_ID:%s", InterfaceToStr(interface), TbfpPayloadIdToStr(frame_id));
#endif
        set_log_level(TBFP, LOG_LEVEL_DEBUG);
#ifdef HAS_TBFP_EXT
        res = tbfp_send_ping(frame_id, interface);
#endif
        log_info_res(TBFP, res, "SendPing");
        set_log_level(TBFP, LOG_LEVEL_INFO);
    } else {
        LOG_ERROR(TBFP, "Usage tbp if id");
    }
    return res;
}

bool tbfp_parse_frame_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t data[512] = {0};
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2array(argv[0], data, sizeof(data), &size);
        log_info_res(TBFP, res, "ParseArray");
        if(false == res) {
            LOG_WARNING(TBFP, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = tbfp_parse_frame(data, size);
        log_info_res(TBFP, res, "ParseFrame");
    } else {
        LOG_ERROR(TBFP, "Usage tbpf HexString");
    }

    return res;
}
