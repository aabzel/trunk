#ifndef SDIO_COMMANDS_H
#define SDIO_COMMANDS_H

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
bool sdio_diag_int_command(int32_t argc, char* argv[]);
bool sdio_diag_low_level_command(int32_t argc, char* argv[]);
bool sdio_diag_command(int32_t argc, char* argv[]);
bool sdio_read_command(int32_t argc, char* argv[]);
bool sdio_write_command(int32_t argc, char* argv[]);
bool sdio_errase_command(int32_t argc, char* argv[]);
bool sdio_init_command(int32_t argc, char* argv[]);
bool sdio_scan_command(int32_t argc, char* argv[]);
bool sdio_init_card_command(int32_t argc, char* argv[]);
bool sd_card_diag_command(int32_t argc, char* argv[]);

#define SDIO_COMMANDS                                                                                                  \
    SHELL_CMD("sdio_diag", "sdd", sdio_diag_command, "SdioDiag"),                                                      \
        SHELL_CMD("sdio_scan", "sds", sdio_scan_command, "SdioScan"),                                                  \
        SHELL_CMD("sdio_diag_ll", "sdl", sdio_diag_low_level_command, "SdioDiagLowLev"),                               \
        SHELL_CMD("sd_card_diag", "cad", sd_card_diag_command, "SdCardDiag"),                                          \
        SHELL_CMD("sdio_init", "sdi", sdio_init_command, "SdioInit"),                                                  \
        SHELL_CMD("sdio_init_card", "sdic", sdio_init_card_command, "SdioInitCard"),                                   \
        SHELL_CMD("sdio_interrupt", "sdin", sdio_diag_int_command, "SdioDiagInt"),                                     \
        SHELL_CMD("sdio_read", "sdr", sdio_read_command, "SdioRead"),                                                  \
        SHELL_CMD("sdio_errase", "sde", sdio_errase_command, "SdioErrase"),                                            \
        SHELL_CMD("sdio_write", "sdw", sdio_write_command, "SdioWriteHexStr"),

#ifdef __cplusplus
}
#endif

#endif /* SDIO_COMMANDS_H */
