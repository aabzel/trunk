#include "max98357_drv.h"

#include <stdint.h>
#include <string.h>

#include "max98357_diag.h"
#include "log.h"
#include "proc_multimedia.h"
#ifdef HAS_I2S
#include "i2s_drv.h"
#endif /**/
#include "code_generator.h"
#include "none_blocking_pause.h"
#include "sw_dac_drv.h"

COMPONENT_GET_NODE(Max98357, max98357)

COMPONENT_GET_CONFIG(Max98357, max98357)

bool max98357_play_1kHz_tone(uint8_t num, double amplitude, double phase_ms) {
    bool res = false;
    const Max98357Config_t* Config = Max98357GetConfig(num);
    if(Config){
        LOG_INFO(MAX98357, "Play Freq:1kHz, Amp:%f, Phase:%f ms", amplitude, phase_ms);

        SwDac_t* SwDaNode = SwDacGetNode(Config->dac_num);
        if(SwDaNode) {
            //SwDaNode->frame_pattern = CHANNEL_BOTH;
            res = play_1kHz_tone(Config->i2s_num, Config->dac_num, amplitude, phase_ms);
            if(res) {
                LOG_INFO(MAX98357, "Play1kHzOk");
            } else {
                LOG_ERROR(MAX98357, "Play1kHzErr");
            }
        }else {
        	LOG_ERROR(MAX98357, "SwDacErr");
        }
    }else{
    	LOG_ERROR(MAX98357, "ConfErr");
    }
    return res;
}

bool max98357_init_one(uint8_t num) {
    bool res = false;
    set_log_level(MAX98357, LOG_LEVEL_DEBUG);
    LOG_WARNING(MAX98357, "%u Init", num);
    const Max98357Config_t* Config = Max98357GetConfig(num);
    if(Config) {
        LOG_INFO(MAX98357, "MAX98357%u SpotConfig", num);
#ifdef HAS_MAX98357_DIAG
        Max98357DiagConfig(Config);
#endif
        Max98357Handle_t* Node = Max98357GetNode(num);
        if(Node) {
            Node->i2s_num = Config->i2s_num;
            Node->dac_num = Config->dac_num;

#ifdef HAS_NORTOS
            res= max98357_play_1kHz_tone(num, 2500, 0.0);
            res = wait_in_loop_ms(1000);
#ifdef HAS_I2S
            //res = play_1kHz_tone(Node->i2s_num , Node->dac_num, 2500, 0.0);
            res = i2s_dma_stop(Node->i2s_num);
#endif /*HAS_I2S*/

#endif /*HAS_NORTOS*/
            Node->init_done = true;
            res = true;
        } else {
            LOG_ERROR(MAX98357, "MAX98357%u HandleErr", num);
            res = false;
        }
    } else {
        LOG_DEBUG(MAX98357, "MAX98357%u NoConfig", num);
        res = false;
    }
    set_log_level(MAX98357, LOG_LEVEL_INFO);
    return res;
}



COMPONENT_INIT_PATTERT(MAX98357, MAX98357, max98357)


