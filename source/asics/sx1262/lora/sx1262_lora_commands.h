#ifndef SX1262_LORA_COMMANDS_H
#define SX1262_LORA_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

bool sx1262_set_modulation_command(int32_t argc, char* argv[]);
bool sx1262_set_lora_sync_word_command(int32_t argc, char* argv[]);

#define SX1262_LORA_COMMANDS_BASE                                                                                      \
        SHELL_CMD("sx1262_modul", "sxl", sx1262_set_modulation_command, "SX1262 set modulation"),                      \
        SHELL_CMD("sx1262_lora_sync", "sxslsw", sx1262_set_lora_sync_word_command, "SX1262 set lora sync word"),

#ifdef HAS_SX1262_LORA_EX_DEBUG
bool sx1262_set_packet_param_command(int32_t argc, char* argv[]);
bool sx1262_set_cad_command(int32_t argc, char* argv[]);
bool sx1262_set_cad_params_command(int32_t argc, char* argv[]);

#define SX1262_LORA_COMMANDS_DEBUG                                                                                     \
    SHELL_CMD("sx1262CadParm", "sxcp", sx1262_set_cad_params_command, "SX1262 SetCadParam"),                           \
    SHELL_CMD("sx1262Cad", "sxa", sx1262_set_cad_command, "SX1262 Set CAD"),                                           \
    SHELL_CMD("sx1262SetPackParam", "sxpp", sx1262_set_packet_param_command, "SX1262 set packet param"),

#else
#define SX1262_LORA_COMMANDS_DEBUG
#endif

#define SX1262_LORA_COMMANDS                                                                                                \
    SX1262_LORA_COMMANDS_BASE                                                                                               \
    SX1262_LORA_COMMANDS_DEBUG

#ifdef __cplusplus
}
#endif

#endif /* SX1262_LORA_COMMANDS_H */
