#include "schmitt_trigger_config.h"

#include "data_utils.h"
#include "log.h"

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

#ifdef HAS_AUTO_VOLUME
#include "auto_volume_config.h"
#endif

#ifdef HAS_BLE_AUDIO
#include "le_audio.h"
#endif

#ifdef HAS_WM8731
#include "wm8731_drv.h"
#endif

#ifdef HAS_MAX9860
#include "max9860_drv.h"
#endif


static bool schmitt_trigger1_proc_up(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Up");
    LedHandle_t* LedNode = LedGetNode(AutoVolumeItem.led_num);
    if(LedNode){
        res = led_mono_off(  LedNode);
    }

#ifdef HAS_BLE_AUDIO_VOLUME
    int ret = 0;
    ret = le_audio_pause();
    if(ret) {
        LOG_ERROR(AUTO_VOLUME, "LeAudioPauseErr %d=%s", ret, ErrNo2Str(ret));
        res = true;
    } else {
        res = true;
        Node->on = false;
    }
#endif
#ifdef HAS_MAX9860
    res = max9860_attenuation_set(AutoVolumeItem.off_gain);
#endif

#ifdef HAS_WM8731
    int8_t left = Dist2Volume(AutoVolumeItem.distance_m);
    int8_t right = Dist2Volume(AutoVolumeItem.distance_m);
    LOG_DEBUG(AUTO_VOLUME, "L:%d,R:%d dB", left, right);
    res = wm8731_set_volume(left, right);
#endif /*HAS_WM8731*/

    return res;
}

static bool schmitt_trigger1_proc_down(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Down");
    LedHandle_t* LedNode = LedGetNode(AutoVolumeItem.led_num);
    if(LedNode){
        res = led_mono_on(  LedNode);
    }

#ifdef HAS_BLE_AUDIO_VOLUME
    if(false == AutoVolumeItem.on) {
        int ret = 0;
        ret = le_audio_play();
        if(ret) {
            LOG_ERROR(AUTO_VOLUME, "LeAudioPlayErr %d=%s", ret, ErrNo2Str(ret));
            res = false;
        } else {
            res = true;
            AutoVolumeItem.on = true;
        }
    }
#endif

#ifdef HAS_MAX9860
    res = max9860_attenuation_set(AutoVolumeItem.on_gain);
#endif

#ifdef HAS_WM8731
    int8_t left = Dist2Volume(AutoVolumeItem.distance_m);
    int8_t right = Dist2Volume(AutoVolumeItem.distance_m);
    LOG_DEBUG(AUTO_VOLUME, "L:%d,R:%d dB", left, right);
    res = wm8731_set_volume(left, right);
#endif /*HAS_WM8731*/
    return res;
}

const SchmittTriggerConfig_t SchmittTriggerConfig[] = {
    {
        .num = 1,
        .up_call_back = schmitt_trigger1_proc_up,
        .down_call_back = schmitt_trigger1_proc_down,
        .hysteresis = 0.2,
        .switching_value = 1.0, /* */
        .name = "UWBdist",
        .valid = true,
    },
};

SchmittTriggerHandle_t SchmittTriggerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t schmitt_trigger_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SchmittTriggerInstance);
    cnt2 = ARRAY_SIZE(SchmittTriggerConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
