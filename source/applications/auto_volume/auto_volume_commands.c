#include "auto_volume_commands.h"

#include "log.h"
#include "auto_volume_diag.h"
#include "auto_volume_config.h"
#include "auto_volume.h"

bool auto_volume_diag_command(int32_t argc, char *argv[]) {
    bool res = false;
    if (0 == argc) {
        res = true;
    }

    if (res) {
        res = auto_volume_diag();
    }
    return res;
}

static AutoVolumeCmd_t Letter2VolCmd(char letter) {
    AutoVolumeCmd_t cmd = AUTO_VOLUME_UNDEF;
    switch (letter) {
    case 'd':
    case '2':
    case '-':
        cmd = AUTO_VOLUME_DOWN;
        break;

    case '8':
    case 'u':
    case '+':
        cmd = AUTO_VOLUME_UP;
        break;
    default:
        cmd = AUTO_VOLUME_UNDEF;
        break;
    }
    return cmd;
}

bool auto_volume_set_command(int32_t argc, char *argv[]) {
    bool res = false;
    AutoVolumeCmd_t cmd = AUTO_VOLUME_UNDEF;
    if (1 == argc) {
        res = true;
        char letter = argv[0][0];
        cmd = Letter2VolCmd(letter);
        LOG_INFO(AUTO_VOLUME, "letter %c", letter);
    }

    if (res) {
        res = auto_volume_set(&AutoVolumeItem, cmd);
        if (res) {
            LOG_INFO(AUTO_VOLUME, "volumeSet %s Ok", VolumeCmd2Str(cmd));
        } else {
            LOG_ERROR(AUTO_VOLUME, "volumeSet %s Err", VolumeCmd2Str(cmd));
        }
    }
    return res;
}

