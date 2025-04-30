
#include "uds_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "uds.h"
#include "uds_diag.h"
#include "writer_generic.h"

bool uds_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t interface = IF_UNDEF;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &interface);
        if(false == res) {
            LOG_ERROR(UDS, "ParseErr if %s", argv[0]);
        }
    }

    if(2 < argc) {
        LOG_ERROR(UDS, "Usage: tbfpd if");
    }
    if(res) {
        res = false;
#ifdef HAS_UDS_DIAG
        res = uds_diag();
#endif
    }
    return res;
}

bool uds_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint8_t array[256];
    size_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UDS, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], array, sizeof(array), &size);
        if(false == res) {
            LOG_WARNING(UDS, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)array, sizeof(array), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = uds_send(num, array, size);
        if(res) {
            LOG_INFO(UDS, "SendOk");
        } else {
            LOG_ERROR(UDS, "SendErr");
        }
    } else {
        LOG_ERROR(UDS, "Usage  uds Num HexArray");
    }

    return res;
}

bool uds_read_data_by_identifier_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint16_t did = 0x0001; // 0x0006
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UDS, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &did);
        if(false == res) {
            LOG_ERROR(UDS, "ParseErr DID %s", argv[1]);
        }
    }

    if(res) {
        res = uds_read_data_by_identifier(num, did);
        if(res) {
            LOG_INFO(UDS, "Ok");
        } else {
            LOG_ERROR(UDS, "Err");
        }
    } else {
        LOG_ERROR(UDS, "Usage  udi Num DID");
    }

    return res;
}

bool uds_start_routine_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint16_t routine_identifier = 0;
    if(1 <= argc) {
        res = try_str2uint16(argv[0], &routine_identifier);
        if(false == res) {
            LOG_ERROR(UDS, "ParseErr RI %s", argv[0]);
        }
    }

    if(res) {
        res = uds_start_routine((UdsRoutineIdentifier_t)routine_identifier);
        if(res) {
            LOG_INFO(UDS, "RoutintStartOk");
        } else {
            LOG_ERROR(UDS, "RoutintStartErr");
        }
    } else {
        LOG_ERROR(UDS, "Usage  usr RI");
    }

    return res;
}

bool uds_did_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UDS, "ParseErr Num %s", argv[0]);
        }
    }

    if(res) {
        res = uds_did_diag(num);
        if(res) {
            LOG_INFO(UDS, "Ok");
        } else {
            LOG_ERROR(UDS, "Err");
        }
    } else {
        LOG_ERROR(UDS, "Usage udid Num");
    }

    return res;
}
