#include "pdm_commands.h"

#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "pdm_diag.h"
#include "pdm_drv.h"

bool pdm_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool on_off = false;
    uint8_t mode = MIC_MODE_SINGLE;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PDM, "ParseErrindex %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(PDM, "ParseErrindex %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &mode);
        if(false == res) {
            LOG_ERROR(PDM, "ParseMode %s", argv[2]);
        }
    }

    if(res) {
        res = pdm_ctrl(num, on_off, (MicMode_t)mode);
    } else {
        LOG_ERROR(PDM, "Usage: pde PdmNum OnOff Mode");
    }
    return res;
}

bool pdm_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = pdm_init();
    }
    return res;
}

bool pdm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = pdm_diag();
        if(res) {
            LOG_INFO(PDM, "DiagOk");
        } else {
            LOG_ERROR(PDM, "DiagErr");
        }
    } else {
        LOG_ERROR(PDM, "Usage: pdd");
    }
    return res;
}

bool pdm_sample_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PDM, "ParseErrindex %s", argv[0]);
        }
    }

    if(res) {
        res = pdm_print_sample(num);
        if(res) {
            LOG_INFO(PDM, "Ok %u", num);
        } else {
            LOG_ERROR(PDM, "Err %u", num);
        }
    } else {
        LOG_ERROR(PDM, "Usage: pdm Num");
    }
    return res;
}

bool pdm_calc_dft_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PDM, "ParseErrindex %s", argv[0]);
        }
    }

    if(res) {
        res = pdm_calc_dft(num);
        if(res) {
            LOG_INFO(PDM, "Ok %u", num);
        } else {
            LOG_ERROR(PDM, "Err %u", num);
        }
    } else {
        LOG_ERROR(PDM, "Usage: pdf Num");
    }
    return res;
}

bool pdm_listen_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t duration_ms = 0;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PDM, "ParseErrindex %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &duration_ms);
        if(false == res) {
            LOG_ERROR(PDM, "Parse TimeOut %s", argv[1]);
        }
    }

    if(res) {
        res = pdm_listen(num, duration_ms);
        if(res) {
            LOG_INFO(PDM, "Ok %u", num);
        } else {
            LOG_ERROR(PDM, "Err %u", num);
        }
    } else {
        LOG_ERROR(PDM, "Usage: pdl Num DurationMs");
    }

    return res;
}
