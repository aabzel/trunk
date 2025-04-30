#include "ble_audio_commands.h"

#include "le_audio.h"
#include "log.h"
#include "zephyr_diag.h"

bool ble_audio_play_command(int32_t argc, char* argv[]) {
    bool res = false;
    int ret = le_audio_play();
    if(ret) {
        LOG_ERROR(BLE_AUDIO, "PlayErr %d=%s", ret, ErrNo2Str(ret));
    } else {
        LOG_INFO(BLE_AUDIO, "Play");
        res = true;
    }

    if(res) {

    } else {
        LOG_ERROR(UART, "Usage: bapl");
    }

    return res;
}

bool ble_audio_pause_command(int32_t argc, char* argv[]) {
    bool res = false;
    int ret = le_audio_pause();
    if(ret) {
        LOG_ERROR(BLE_AUDIO, "PauseErr %d=%s", ret, ErrNo2Str(ret));
    } else {
        LOG_INFO(BLE_AUDIO, "Pause");
        res = true;
    }

    if(res) {

    } else {
        LOG_ERROR(UART, "Usage: bapa");
    }
    return res;
}

bool ble_audio_send_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t data[256];
    size_t size = 0;

    if(1 <= argc) {
        res = try_str2array(argv[0], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(UART, "ExtractHexArrayErr  [%s]", argv[0]);
            snprintf((char*)data, sizeof(data), "%s", argv[0]);
            size = strlen(argv[0]);
            res = true;
        } else {
        }
    }

    if(res) {
        int ret = le_audio_send(data, size);
        if(ret) {
            LOG_ERROR(BLE_AUDIO, "SendErr %d=%s", ret, ErrNo2Str(ret));
        } else {
            LOG_INFO(BLE_AUDIO, "Send");
        }
    } else {
        LOG_ERROR(UART, "Usage: bas hex_string");
    }
    return res;
}

bool ble_audio_disable_command(int32_t argc, char* argv[]) {
    bool res = false;
    int ret = le_audio_disable();
    if(ret) {
        LOG_ERROR(BLE_AUDIO, "DisableErr %d=%s", ret, ErrNo2Str(ret));
    } else {
        LOG_INFO(BLE_AUDIO, "Disable");
        res = true;
    }

    if(res) {

    } else {
        LOG_ERROR(UART, "Usage: bad");
    }

    return res;
}

bool ble_audio_volume_mute_command(int32_t argc, char* argv[]) {
    bool res = false;
    int ret = le_audio_volume_mute();
    if(ret) {
        LOG_ERROR(BLE_AUDIO, "VolMuteErr %d=%s", ret, ErrNo2Str(ret));
    } else {
        LOG_INFO(BLE_AUDIO, "Mute");
        res = true;
    }

    if(res) {

    } else {
        LOG_ERROR(UART, "Usage: bavm");
    }
    return res;
}

bool ble_audio_volume_down_command(int32_t argc, char* argv[]) {
    bool res = false;
    int ret = le_audio_volume_down();
    if(ret) {
        LOG_ERROR(BLE_AUDIO, "VolDownErr %d=%s", ret, ErrNo2Str(ret));
    } else {
        LOG_INFO(BLE_AUDIO, "VoluneDownOK");
        res = true;
    }

    if(res) {

    } else {
        LOG_ERROR(UART, "Usage: bavd");
    }
    return res;
}

bool ble_audio_volume_up_command(int32_t argc, char* argv[]) {
    bool res = false;
    int ret = le_audio_volume_up();
    if(ret) {
        LOG_ERROR(BLE_AUDIO, "VolUpErr %d=%s", ret, ErrNo2Str(ret));
    } else {
        LOG_INFO(BLE_AUDIO, "VolumeUp");
        res = true;
    }

    if(res) {

    } else {
        LOG_ERROR(UART, "Usage: bavu");
    }
    return res;
}
