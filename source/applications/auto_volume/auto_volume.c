#include "auto_volume.h"

#include "auto_volume_dep.h"
#include "data_utils.h"

#ifdef HAS_SCHMITT_TRIGGER
#include "schmitt_trigger.h"
#endif

#ifdef HAS_ZEPHYR
#include "zephyr_diag.h"
#endif

#ifdef HAS_BLE_AUDIO
#include "le_audio.h"
#endif

#ifdef HAS_DISTANCE
#include "distance_drv.h"
#endif

#include "log.h"
#ifdef HAS_WM8731
#include "wm8731_drv.h"
#endif

#ifdef HAS_MAX9860
#include "max9860_drv.h"
#endif

#include "auto_volume_diag.h"

#ifdef HAS_WM8731
int8_t Dist2Volume(double dist_m) {
    int8_t code8 = 0;
    double code_f = AUTO_VOLUME_B_DEFAULT + AUTO_VOLUME_A_DEFAULT * dist_m;
    int32_t code32 = (int32_t)(code_f);
    code8 = (int8_t)int32_range_limiter(code32, -127, 127);
    LOG_DEBUG(AUTO_VOLUME, "Dist %f m, Code %f, Volume %d dB, Volume32 %d dB", dist_m, code_f, code8, code32);
    return code8;
}
#endif

#if 0
#ifdef HAS_MAX9860
Gain_t Dist2Max9860Attenuation(double dist_m) {
    Gain_t gain = -90;
    if(dist_m < 4.0) {
        double gain_f = -46.5 * dist_m + 3.0;
        gain = (Gain_t)gain_f;
        LOG_DEBUG(AUTO_VOLUME, "Dist %4.2f m, Gain %4.0f=%d", dist_m, gain_f, gain);
    }
    return gain;
}

static Gain_t Dist2Max9860AttenuationBinary(const AutoVolumeItem_t* const Node) {
    Gain_t gain = -90;
    if(Node) {
        if(Node->distance_m < 0.9) {
            gain = Node->on_gain;
        } else {
            gain = Node->off_gain;
            LOG_DEBUG(AUTO_VOLUME, "MuteSound");
        }
    }
    LOG_DEBUG(AUTO_VOLUME, "Dist %4.2f m, Gain=%d", Node->distance_m, gain);
    return gain;
}

#endif
#endif

#ifdef HAS_BLE_AUDIO_VOLUME
static bool AutoVolumeDistance2BleAudio(AutoVolumeItem_t* const Node) {
    bool res = false;
    if(Node) {
        int ret = 0;
        if(Node->distance_m < 1.0) {
            if(false == Node->on) {
                ret = le_audio_play();
                if(ret) {
                    LOG_ERROR(AUTO_VOLUME, "LE_AudioPlayErr %d=%s", ret, ErrNo2Str(ret));
                    res = false;
                } else {
                    res = true;
                    Node->on = true;
                }
            }
        } else {
            // if(Node->on) {
            ret = le_audio_pause();
            if(ret) {
                LOG_ERROR(AUTO_VOLUME, "LE_AudioPauseErr %d=%s", ret, ErrNo2Str(ret));
                res = true;
            } else {
                res = true;
                Node->on = false;
            }
            // }
        }
    }
    return res;
}
#endif

#if defined(HAS_MAX9860) && defined(HAS_BLE_AUDIO_VOLUME)
#error "Double Volume Control"
#endif

bool auto_volume_proc(void) {
    bool res = false;

    DistanceHandle_t* DistNode = DistanceGetNode(AutoVolumeItem.dist_num);
    if(DistNode) {
        AutoVolumeItem.distance_m = DistNode->distance_m;
        LOG_DEBUG(AUTO_VOLUME, "DistValid %f m", AutoVolumeItem.distance_m);
        res = true;
    } else {
        AutoVolumeItem.distance_m = 999.0;
        LOG_ERROR(AUTO_VOLUME, "Dist%u NodeErr", AutoVolumeItem.dist_num);
        res = false;
    }

    res = schmitt_trigger_proc_val(AutoVolumeItem.schmitt_trigger_num, AutoVolumeItem.distance_m);
    if(res) {
        LOG_DEBUG(AUTO_VOLUME, "FF%u, Value:%f ProcOk", AutoVolumeItem.schmitt_trigger_num, AutoVolumeItem.distance_m);
    } else {
        LOG_ERROR(AUTO_VOLUME, "SchmittTrigger%u Err", AutoVolumeItem.schmitt_trigger_num);
    }

#ifdef HAS_BLE_AUDIO_VOLUME
    int ret = 0;
    SchmittTriggerState_t state = schmitt_trigger_get_state(AutoVolumeItem.schmitt_trigger_num);
    switch(state) {
    case SCHMITT_TRIGGER_STATE_UP: {
        ret = le_audio_pause();
        if(ret) {
            LOG_DEBUG(AUTO_VOLUME, "LE_AudioPauseErr %d=%s", ret, ErrNo2Str(ret));
            res = true;
        } else {
            res = true;
            AutoVolumeItem.on = false;
        }
    } break;
    case SCHMITT_TRIGGER_STATE_DOWN: {
        ret = le_audio_play();
        if(ret) {
            LOG_DEBUG(AUTO_VOLUME, "LE_AudioPlayErr %d=%s", ret, ErrNo2Str(ret));
            res = false;
        } else {
            res = true;
            AutoVolumeItem.on = true;
        }
    } break;
    }
#endif

#if 0
    res = AutoVolumeDistance2Led(&AutoVolumeItem);
    if(false == res) {
        LOG_DEBUG(AUTO_VOLUME, "LEDdetErr");
    }
#ifdef HAS_MAX9860
    Gain_t gain = Dist2Max9860AttenuationBinary(&AutoVolumeItem);
    LOG_PARN(AUTO_VOLUME, "Proc Dist %4.2f m, Gain %d", AutoVolumeItem.distance_m, gain);
    res = max9860_attenuation_set(gain);
#endif /*HAS_MAX9860*/

#ifdef HAS_WM8731
    int8_t left = Dist2Volume(AutoVolumeItem.distance_m);
    int8_t right = Dist2Volume(AutoVolumeItem.distance_m);
    LOG_DEBUG(AUTO_VOLUME, "L:%d,R:%d dB", left, right);
    res = wm8731_set_volume(left, right);
#endif /*HAS_WM8731*/

#ifdef HAS_BLE_AUDIO_VOLUME
    res = AutoVolumeDistance2BleAudio(&AutoVolumeItem);
    if(false == res) {
        LOG_ERROR(AUTO_VOLUME, "BleAudioVolumeCtrlErr");
    }
#endif

#endif

    return res;
}

static bool auto_volume_up(AutoVolumeItem_t* const Node) {
    bool res = false;
#ifdef HAS_AUDIO
    LOG_WARNING(AUTO_VOLUME, "Up Cur %d dB", Node->on_gain);
    if(Node) {
        if(Node->on_gain < Node->max_gain) {
            Node->on_gain++;
            LOG_INFO(AUTO_VOLUME, "volume New %d dB", Node->on_gain);
            res = true;
        }
    }
#endif
    return res;
}

static bool auto_volume_down(AutoVolumeItem_t* const Node) {
    bool res = false;
#ifdef HAS_AUDIO
    LOG_WARNING(AUTO_VOLUME, "Down Cur %d dB", Node->on_gain);
    if(Node) {
        if(Node->min_gain < Node->on_gain) {
            Node->on_gain--;
            LOG_INFO(AUTO_VOLUME, "volume New %d dB", Node->on_gain);
            res = true;
        }
    }
#endif
    return res;
}

bool auto_volume_set(AutoVolumeItem_t* const Node, AutoVolumeCmd_t cmd) {
    bool res = false;
    LOG_WARNING(AUTO_VOLUME, "TryVolumeSet %s", VolumeCmd2Str(cmd));

    switch(cmd) {
    case AUTO_VOLUME_DOWN: {
        res = auto_volume_down(Node);
    } break;
    case AUTO_VOLUME_UP: {
        res = auto_volume_up(Node);
    } break;
    default:
        res = false;
        break;
    }

    return res;
}

bool auto_volume_init_one(const AutoVolumeConfig_t* const Config, AutoVolumeItem_t* const Node) {
    bool res = true;
    if(Config) {
        AutoVolumeDiagConfig(Config);
        if(Node) {
#ifdef HAS_AUDIO
            Node->off_gain = Config->off_gain;
            Node->min_gain = Config->min_gain;
            Node->max_gain = Config->max_gain;
            Node->on_gain = Config->on_gain;
#endif
            Node->dist_num = Config->dist_num;
            Node->schmitt_trigger_num = Config->schmitt_trigger_num;
            Node->err_cnt = 0;
            Node->on = false;
            Node->valid = true;
            Node->num = 1;
            res = true;
        }
    }
    return res;
}

bool auto_volume_init(void) {
    bool res = true;
    LOG_WARNING(AUTO_VOLUME, "Init");
    res = auto_volume_init_one(&AutoVolumeConfig, &AutoVolumeItem);

#ifdef HAS_NORTOS

#ifdef HAS_WM8731
    res = wm8731_play_freq(2000.0, 64000);
#endif /*HAS_WM8731*/

#ifdef HAS_MAX9860
    res = max9860_attenuation_set(AutoVolumeItem.off_gain);
    res = max9860_play_1kHz_tone(111.0, 0.0);
#endif /*HAS_MAX9860*/

#endif /*HAS_NORTOS*/

    return res;
}
