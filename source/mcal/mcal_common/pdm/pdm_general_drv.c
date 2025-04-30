#include "pdm_drv.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

//#include "c_defines_generated.h"

#include "common_diag.h"
#ifdef HAS_COMPLEX_DIAG
#include "complex_diag.h"
#endif
#include "data_utils.h"
#ifdef HAS_DFT
#include "dft.h"
#endif
#include "float_utils.h"
#include "gpio_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "pdm_diag.h"

PdmHandle_t* PdmGetNode(uint8_t num) {
    PdmHandle_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < pdm_get_cnt(); i++) {
        if(num == PdmInstance[i].num) {
            if(PdmInstance[i].valid) {
                Node = &PdmInstance[i];
                break;
            }
        }
    }
    return Node;
}

const PdmConfig_t* PdmGetConfig(uint8_t num) {
    const PdmConfig_t* Config = 0;
    uint32_t i = 0;
    for(i = 0; i < pdm_get_cnt(); i++) {
        if(num == PdmConfig[i].num) {
            if(PdmConfig[i].valid) {
                Config = &PdmConfig[i];
                break;
            }
        }
    }
    return Config;
}

bool pdm_is_init(uint8_t num) {
    bool res = false;
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        res = Node->init_done;
    }
    return res;
}

bool pdm_init(void) {
    bool res = false;
    LOG_WARNING(PDM, "Init..");
    uint8_t ok_cnt = 0;
    uint8_t num = 0;
    for(num = 0; num < PDM_COUNT; num++) {
        res = pdm_init_one(num);
        if(res) {
            LOG_INFO(PDM, "PDM%u InitOk", num);
            ok_cnt++;
        } else {
            LOG_DEBUG(PDM, "PDM%u InitErr", num);
        }
    }

    if(ok_cnt) {
        LOG_INFO(PDM, "Init %u PDMs", ok_cnt);
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool PdmIsValidConfig(const PdmConfig_t* const Config) {
    bool res = false;
    if(Config) {
        if(Config->sample_rate_hz) {
            if(Config->frequency_hz) {
                res = gpio_is_valid_pad(Config->PadClk.byte);
                if(res) {
                    res = gpio_is_valid_pad(Config->PadDin.byte);
                }
            }
        }
    }
    return res;
}

bool pdm_proc(void) {
    bool res = false;
    LOG_PARN(PDM, "proc..");
    uint8_t ok_cnt = 0;
    uint8_t num = 0;
    for(num = 0; num < PDM_COUNT; num++) {
        res = pdm_proc_one(num);
        if(res) {
            LOG_PARN(PDM, "PDM%u ProcOk", num);
            ok_cnt++;
        } else {
            LOG_DEBUG(PDM, "PDM%u ProcErr", num);
        }
    }

    if(ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

#ifdef HAS_DFT
bool pdm_calc_dft_ll(PdmHandle_t* const Node) {
    bool res = false;
    if(Node) {
        double sample_period_s = 1.0 / Node->sample_rate_hz;
        LOG_INFO(PDM, "SampleRate %u Hz, SamplePeriod %u us, %u Samples", Node->sample_rate_hz,
                 SEC_2_USEC(sample_period_s), Node->samples_cnt);
        res = dft_calc((const SampleType_t* const)Node->buf, Node->samples_cnt, Node->dft_mem, Node->samples_cnt,
                       sample_period_s);
#ifdef HAS_COMPLEX_DIAG
        complex_array_print(Node->dft_mem, Node->samples_cnt, sample_period_s, Node->samples_cnt);
        complex_array_print_csv(Node->dft_mem, Node->samples_cnt, sample_period_s, Node->samples_cnt);
#endif
        Node->max_freq = 0.0;
        ft_find_freq(Node->dft_mem, Node->samples_cnt, sample_period_s, &Node->max_freq);
        LOG_INFO(PDM, "Max Freq %f Hz", Node->max_freq);
    }
    return res;
}
#endif

#ifdef HAS_DFT
bool pdm_calc_dft(uint8_t num) {
    bool res = false;
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        res = pdm_calc_dft_ll(Node);
    }
    return res;
}
#endif

bool pdm_listen(uint8_t num, uint32_t duration_ms) {
    bool res = false;
    LOG_INFO(PDM, "PDM%u Listen %u ms", num, duration_ms);
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        res = pdm_ctrl(num, true, MIC_MODE_CONTINUOUS);
        res = wait_in_loop_ms(duration_ms);
        res = pdm_ctrl(num, false, MIC_MODE_CONTINUOUS);
        res = pdm_print_sample(num);
#ifdef HAS_DFT
        res = pdm_calc_dft_ll(Node);
#endif
    }
    return res;
}
