#ifndef BLE_AUDIO_COMMANDS_H
#define BLE_AUDIO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_BLUETOOTH
#error "+HAS_BLUETOOTH"
#endif

bool ble_audio_play_command(int32_t argc, char* argv[]);
bool ble_audio_pause_command(int32_t argc, char* argv[]);
bool ble_audio_send_command(int32_t argc, char* argv[]);
bool ble_audio_disable_command(int32_t argc, char* argv[]);
bool ble_audio_volume_mute_command(int32_t argc, char* argv[]);
bool ble_audio_volume_down_command(int32_t argc, char* argv[]);
bool ble_audio_volume_up_command(int32_t argc, char* argv[]);

#define BLE_AUDIO_COMMANDS                                                                               \
    SHELL_CMD("ble_audio_play", "bapl", ble_audio_play_command, "BleAudioPlay"),                         \
    SHELL_CMD("ble_audio_pause", "bapa", ble_audio_pause_command, "BleAudioPause"),                      \
    SHELL_CMD("ble_audio_send", "bas", ble_audio_send_command, "BleAudioSend"),                          \
    SHELL_CMD("ble_audio_disable", "bad", ble_audio_disable_command, "BleAudioDisable"),                 \
    SHELL_CMD("ble_audio_volume_mute", "bavm", ble_audio_volume_mute_command, "BleAudioVolumeMute"),     \
    SHELL_CMD("ble_audio_volume_down", "bavd", ble_audio_volume_down_command, "BleAudioVolimeDown"),     \
    SHELL_CMD("ble_audio_volume_up", "bavu", ble_audio_volume_up_command, "BleAudioVolumeUp"),

#ifdef __cplusplus
}
#endif

#endif /* BLE_AUDIO_COMMANDS_H */
