#ifndef SDIO_CUSTOM_COMMANDS_H
#define SDIO_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

#ifndef HAS_SDIO_COMMANDS
#error "+HAS_SDIO_COMMANDS"
#endif

// OCR CID RCA DSR CSD SCR SSR CSR
bool sdio_custom_diag_command(int32_t argc, char* argv[]);
bool sdio_read_command(int32_t argc, char* argv[]);
bool sdio_write_command(int32_t argc, char* argv[]);
bool sdio_errase_command(int32_t argc, char* argv[]);
bool sdio_custom_init_command(int32_t argc, char* argv[]);
bool sdio_init_card_command(int32_t argc, char* argv[]);

bool sdio_scan_command(int32_t argc, char* argv[]);
bool sdio_diag_int_command(int32_t argc, char* argv[]);
bool sdio_diag_low_level_command(int32_t argc, char* argv[]);
bool sd_card_diag_command(int32_t argc, char* argv[]);
bool sdio_clk_div_command(int32_t argc, char* argv[]);

#define SDIO_CUSTOM_DIAG_COMMANDS                                                                                      \
        SHELL_CMD("sdio_custom_scan", "sds", sdio_scan_command, "SdioCustomScan"),                                                  \
        SHELL_CMD("sdio_custom_diag_custom", "sddc", sdio_custom_diag_command, "SdioCustomDiag"),                            \
        SHELL_CMD("sdio_custom_diag_ll", "sdl", sdio_diag_low_level_command, "SdioDiagLowLev"),                               \
        SHELL_CMD("sd_custom_card_diag", "cad", sd_card_diag_command, "SdCardCustomDiag"),

#define SDIO_CUSTOM_COMMANDS                                                                                           \
        SDIO_CUSTOM_DIAG_COMMANDS                                                                                      \
        SHELL_CMD("sdio_clk_div", "sdcd", sdio_clk_div_command, "SdioClockDiv"),                                       \
        SHELL_CMD("sdio_custom_init", "sdci", sdio_custom_init_command, "SdioCustomInit"),                            \
        SHELL_CMD("sdio_custom_init_card", "sdic", sdio_init_card_command, "SdioCustomInitCard"),                                   \
        SHELL_CMD("sdio_custom_interrupt", "sdin", sdio_diag_int_command, "SdioCustomDiagInt"),                                     \
        SHELL_CMD("sdio_custom_read", "sdr", sdio_read_command, "SdioCustomRead"),                                                  \
        SHELL_CMD("sdio_custom_errase", "sde", sdio_errase_command, "SdioCustomErrase"),                                            \
        SHELL_CMD("sdio_custom_write", "sdw", sdio_write_command, "SdioWriteHexStr"),

#ifdef __cplusplus
}
#endif

#endif /* SDIO_CUSTOM_COMMANDS_H */
