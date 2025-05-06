#ifndef FW_LOADER_COMMANDS_H
#define FW_LOADER_COMMANDS_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

bool fw_loader_ping_command(int32_t argc, char* argv[]);
bool fw_loader_upload_command(int32_t argc, char* argv[]);
bool fw_loader_download_command(int32_t argc, char* argv[]);

#define FW_LOADER_BASE_COMMANDS                                                                        \
    SHELL_CMD("fw_loader_upload", "fwl", fw_loader_upload_command, "FwLoaderUpLoad"),                  \
    SHELL_CMD("fw_loader_download", "fwd", fw_loader_download_command, "FwLoaderDownload"),            \
    SHELL_CMD("fw_loader_ping", "fwp", fw_loader_ping_command, "FwLoaderPing"),

#define FW_LOADER_COMMANDS                                                                             \
    FW_LOADER_BASE_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* FW_LOADER_COMMANDS_H */
