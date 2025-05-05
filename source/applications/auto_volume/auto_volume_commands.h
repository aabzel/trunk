#ifndef AUTO_VOLUME_COMMAND_H
#define AUTO_VOLUME_COMMAND_H

#include <stdbool.h>
#include <stdint.h>

bool auto_volume_diag_command(int32_t argc, char *argv[]);
bool auto_volume_set_command(int32_t argc, char *argv[]);

#define AUTO_VOLUME_COMMANDS                                                         \
   SHELL_CMD("auto_volume_diag", "avd", auto_volume_diag_command, "AutoVolumeDiag"), \
   SHELL_CMD("auto_volume_set", "avs", auto_volume_set_command, "AutoVolumeSet"),

#endif /* AUTO_VOLUME_COMMAND_H */
