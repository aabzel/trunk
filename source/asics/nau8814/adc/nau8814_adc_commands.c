#include "nau8814_adc_commands.h"

#include "convert.h"
#include "log.h"
#include "nau8814_adc.h"
#include "nau8814_adc_diag.h"
#include "nau8814_diag.h"
#include "nau8814_drv.h"

bool nau8814_adc_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = nau8814_adc_diag(num);
        if(res) {
            Nau8814Handle_t* Node = Nau8814GetNode(num);
            if(Node) {
                LOG_INFO(NAU8814, "%s", Nau8814NodeToStr(Node));
            }
        } else {
        }
    } else {
        LOG_ERROR(NAU8814, "Usage: nad Num");
    }
    return res;
}

/*
 nal 1000
*/
bool nau8814_listen_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t duration_ms = 1000;
    double exp_freq_hz = 0.0;
#ifdef HAS_I2S
    log_level_get_set(I2S, LOG_LEVEL_INFO);
#endif
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &duration_ms);
        if(false == res) {
            LOG_ERROR(NAU8814, "ParseErr DurationMs %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &exp_freq_hz);
        if(false == res) {
            LOG_ERROR(NAU8814, "ParseErr ExpFreqHz %s", argv[1]);
        }
    }

    if(res) {
        res = nau8814_listen(1, duration_ms);
    } else {
        LOG_ERROR(NAU8814, "Usage: nal duration_ms");
    }

    return res;
}
