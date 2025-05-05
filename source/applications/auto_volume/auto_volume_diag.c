#include "auto_volume_diag.h"

#include "log.h"
#include "auto_volume.h"
#include "auto_volume_config.h"

const char* VolumeCmd2Str(AutoVolumeCmd_t cmd) {
    const char* name ="?";
    switch((int8_t)cmd) {
        case AUTO_VOLUME_DOWN: name ="Down";break;
        case AUTO_VOLUME_UP: name ="Up";break;
        default : name ="?";break;
    }
    return name;
}

bool AutoVolumeDiagConfig(const AutoVolumeConfig_t* const Config){
    bool res = false;
    if(Config){
#ifdef HAS_AUDIO
        LOG_INFO(AUTO_VOLUME, "Conf: FF:%u, Min %d, Max %d, Off %d, On %d dB",
                Config->schmitt_trigger_num,
                Config->min_gain,
                Config->max_gain,
                Config->off_gain,
                Config->on_gain);
#endif
        res = true;
    }

    return res;
}

bool AutoVolumeDiagNode(const AutoVolumeItem_t* const Node){
    bool res = false;
    if(Node){
#ifdef HAS_AUDIO
        LOG_INFO(AUTO_VOLUME, "Node: Min %d, Max %d, Off %d, On %d dB, Err %u",
                Node->min_gain,
                Node->max_gain,
                Node->off_gain,
                Node->on_gain,
                Node->err_cnt);
#endif
        res = true;
    }

    return res;
}

bool auto_volume_diag(void) {
    bool res = false;
    LOG_INFO(AUTO_VOLUME, "Diag");
    res= AutoVolumeDiagConfig(&AutoVolumeConfig);
    res= AutoVolumeDiagNode(&AutoVolumeItem);
    return res;
}
