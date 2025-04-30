#include "proc_multimedia.h"

#ifdef HAS_AUDIO
#include "audio_diag.h"
#include "audio_types.h"
#endif

#include "common_functions.h"
#include "log.h"
#ifdef HAS_SW_DAC
#include "sw_dac_drv.h"
#endif

#ifdef HAS_I2S
#include "i2s_mcal.h"
#endif

#ifdef HAS_WM8731
#include "wm8731_drv.h"
#endif

#ifdef HAS_LC3
#include "lc3_drv.h"
#endif

#ifdef HAS_USB_TO_I2S
#include "usb_to_i2s_drv.h"
#endif /*HAS_USB_TO_I2S*/

#ifdef HAS_SI4703
#include "si4703_const.h"
#include "si4703_drv.h"
#endif /*HAS_SI4703*/

#ifdef HAS_SI4737
#include "si4737_drv.h"
#endif /*HAS_SI4737*/

#ifdef HAS_BC127
#include "bc127_drv.h"
#endif /*HAS_BC127*/

#ifdef HAS_BT1026
#include "bt1026_drv.h"
#endif /*HAS_BT1026*/

#ifdef HAS_DAC
#include "dac_drv.h"
#endif /*HAS_DAC*/

#ifdef HAS_MAX98357
#include "max98357_drv.h"
#endif /*HAS_MAX98357*/

#ifdef HAS_FDA801
#include "fda801_drv.h"
#endif /*HAS_FDA801*/

#ifdef HAS_TASK
#include "task_config.h"
#include "task_info.h"
#endif

#ifdef HAS_MULTIMEDIA_LEGACY
void super_cycle_multimedia(uint64_t loop_start_time_us) {
#ifdef HAS_FDA801
    measure_task_interval(TASK_ID_FDA801, FDA801_POLL_PERIOD_US, fda801_proc, loop_start_time_us);
#endif /*HAS_FDA801*/

#ifdef HAS_SI4703
    measure_task_interval(TASK_ID_SI4703, SI4703_POLL_PERIOD_US, si4703_proc, loop_start_time_us);
#endif /*HAS_SI4737*/

#ifdef HAS_SI4737
    measure_task_interval(TASK_ID_SI4737, SI4737_POLL_PERIOD_US, si4737_proc, loop_start_time_us);
#endif /*HAS_SI4737*/

#ifdef HAS_BC127
    measure_task_interval(TASK_ID_BC127, BC127_PERIOD_US, bc127_proc, loop_start_time_us);
#endif /*HAS_BC127*/

#ifdef HAS_BT1026
    measure_task_interval(TASK_ID_BT1026, BT1026_PERIOD_US, bt1026_proc, loop_start_time_us);
#endif /*HAS_BT1026*/

#ifdef HAS_USB_TO_I2S
    usb_to_i2s_proc();
#endif
}
#endif

#if 0
bool multimedia_init(void) {
    bool res = true;
    LOG_INFO(SYS, "InitMultimedia");
#ifdef HAS_FDA801
    res = try_init(fda801_init(), "Fda801") && res;
#endif /*HAS_FDA801*/

#ifdef HAS_BC127
    res = try_init(bc127_init(), "BC127") && res;
#endif /*HAS_BC127*/

#ifdef HAS_BT1026
    res = try_init(bt1026_init(), "BT1026") && res;
#endif /*HAS_BT1026*/

#ifdef HAS_WM8731
    res = try_init(wm8731_init(), "WM8731") && res;
#endif /*HAS_WM8731*/

#ifdef HAS_MAX98357
    res = try_init(max98357_init(), "max98357") && res;
#endif /*HAS_MAX98357*/

#ifdef HAS_SI4703
    res = try_init(si4703_init(), "Si4703") && res;
#endif /*HAS_SI4703*/

#ifdef HAS_SI4737
    res = try_init(si4737_init(), "Si4737") && res;
#endif /*HAS_SI4737*/

#ifdef HAS_LC3
    res = try_init(lc3_init(), "LC3") && res;
#endif

#ifdef HAS_USB_TO_I2S
    res = try_init(usb_to_i2s_init(), "Usb>I2s") && res;
#endif /*HAS_USB_TO_I2S*/

    return res;
}
#endif

#ifdef HAS_SW_DAC
FramePattern_t SampleMode2FramePattern(SampleMode_t sample_mode) {
    FramePattern_t patteen = CHANNEL_UNDEF;
    switch((uint8_t)sample_mode) {
    case SAMPLE_MODE_MONO:
        patteen = CHANNEL_ONLY_LEFT;
        break;
    case SAMPLE_MODE_STEREO:
        patteen = CHANNEL_BOTH;
        break;
    default:
        break;
    }
    return patteen;
}
#endif

#if defined(HAS_SW_DAC) && defined(HAS_I2S)
bool check_sample_size(uint8_t i2s_num, uint8_t dac_num) {
    bool res = false;
    I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
    if(I2sNode) {
        SwDac_t* SwDacNode = SwDacGetNode(dac_num);
        if(SwDacNode) {
            switch(I2sNode->data_format) {
            case I2S_DATA_FORMAT_8B:
                res = sw_dac_match_sample_size(SwDacNode, 8);
                break;
            case I2S_DATA_FORMAT_16B:
                res = sw_dac_match_sample_size(SwDacNode, 16);
                break;
            case I2S_DATA_FORMAT_16B_EXTENDED:
                res = sw_dac_match_sample_size(SwDacNode, 16);
                break;
            case I2S_DATA_FORMAT_24B:
                res = sw_dac_match_sample_size(SwDacNode, 24);
                break;
            case I2S_DATA_FORMAT_32B:
                res = sw_dac_match_sample_size(SwDacNode, 32);
                break;
            default: {
                LOG_ERROR(I2S, "UndefFrameFormat: %u", I2sNode->data_format);
                res = false;
            } break;
            }
        }
    }
    return res;
}
#endif

bool play_1kHz_tone(uint8_t i2s_num, uint8_t dac_num, double amplitude, double phase_ms) {
    bool res = false;

#ifdef HAS_I2S
    res = i2s_dma_stop(i2s_num);
#endif

#ifdef HAS_SW_DAC
    LOG_INFO(SW_DAC, "I2S%u, DAC%u, Amplitude: %f, Phase: %f", i2s_num, dac_num, amplitude, phase_ms);
    res = sw_dac_set_sin(dac_num, 1000.0, (SampleType_t)amplitude, phase_ms, (SampleType_t)0);
    if(res) {
        res = false;
#ifdef HAS_I2S
        res = check_sample_size(i2s_num, dac_num);
#endif /*HAS_I2S*/

        if(res) {
            LOG_INFO(SW_DAC, "SampleBittnerssMatch!");
            res = sw_dac_set_static_period_48k_1000hz_word(dac_num) && res;
            if(res) {
                res = false;
#ifdef HAS_I2S
                LOG_INFO(SW_DAC, "Play1kHzTone");
                res = i2s_play_static_tx(i2s_num, dac_num, true);
#endif /*HAS_I2S*/
                if(res) {
                    LOG_INFO(SW_DAC, "I2S%u Play DAC%u Ok", i2s_num, dac_num);
                } else {
                    res = false;
                    LOG_ERROR(SW_DAC, "I2S%u Play DAC%u Err", i2s_num, dac_num);
                }
            } else {
                LOG_ERROR(SW_DAC, "Calc1kHzToneErr");
                res = false;
            }
        } else {
            LOG_ERROR(SW_DAC, "SampleBittnerssDiscrepancy!");
        }

    } else {
        LOG_ERROR(SW_DAC, "SetDACerr");
        res = false;
    }
#endif /*HAS_SW_DAC*/

    return res;
}
