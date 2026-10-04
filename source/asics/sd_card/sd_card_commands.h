#ifndef SD_CARD_COMMAND_H
#define SD_CARD_COMMAND_H

#include "std_includes.h"
#include "sd_card_dependencies.h"

#ifndef HAS_SD_CARD_COMMANDS
#error "+HAS_SD_CARD_COMMANDS"
#endif

bool cmd_sd_card_diag(int32_t argc, char* argv[]);
bool cmd_sd_card_power_on(int32_t argc, char* argv[]);
bool cmd_sd_card_read_sector(int32_t argc, char* argv[]);
bool cmd_sd_card_init(int32_t argc, char* argv[]);
bool cmd_sd_card_send_command(int32_t argc, char* argv[]);
bool cmd_sd_card_74ones_command(int32_t argc, char* argv[]);
bool cmd_sd_card_ioctl(int32_t argc, char* argv[]);
bool cmd_sd_card_write_sector(int32_t argc, char* argv[]);
bool cmd_sd_card_read_csd_command(int32_t argc, char* argv[]);
bool sd_card_read_csr_command(int32_t argc, char* argv[]);
bool sd_card_read_ocr_command(int32_t argc, char* argv[]);
bool cmd_sd_card_read_cid_command(int32_t argc, char* argv[]);
bool cmd_sd_card_read_ssr_command(int32_t argc, char* argv[]);
bool sd_card_read_sr_command(int32_t argc, char* argv[]);

#define SD_CARD_COMMANDS                                                                                               \
    SHELL_CMD("sd_card_read_sr", "sdrsr", sd_card_read_sr_command, "SdCardReadStatusRegister"),                        \
    SHELL_CMD("cmd_sd_card_read_ocr", "sdrocr", sd_card_read_ocr_command, "SdCardReadRegOcr"),                         \
    SHELL_CMD("cmd_sd_card_read_ssr", "sdrssr", cmd_sd_card_read_ssr_command, "SdCardReadRegSdStatus"),                \
    SHELL_CMD("cmd_sd_card_read_csr", "sdrcs", sd_card_read_csr_command, "SdCardReadRegCardStatus"),                   \
    SHELL_CMD("cmd_sd_card_read_cid", "sdrcid", cmd_sd_card_read_cid_command, "SdCardReadRegSid"),                     \
    SHELL_CMD("sd_power", "sdpon", cmd_sd_card_power_on, "SD send power on"),                                          \
        SHELL_CMD("sd_ones", "sdon", cmd_sd_card_74ones_command, "SD send 74 ones"),                                   \
        SHELL_CMD("sd_cmd", "sdc", cmd_sd_card_send_command, "SdCardSendCommand"),                                     \
        SHELL_CMD("sd_read_csd", "sdrcsd", cmd_sd_card_read_csd_command, "SdReadCsdRegcommand"),                       \
        SHELL_CMD("sd_init", "sdi", cmd_sd_card_init, "SD init"),                                                      \
        SHELL_CMD("sd_ctl", "sdt", cmd_sd_card_ioctl, "SD ioctl"),                                                     \
        SHELL_CMD("sd_read", "sdr", cmd_sd_card_read_sector, "SD read sector"),                                        \
        SHELL_CMD("sd_write", "sdw", cmd_sd_card_write_sector, "SD write sector"),                                     \
        SHELL_CMD("sd_diag", "sdd", cmd_sd_card_diag, "SD diag"),

#endif /* SD_CARD_COMMAND_H */
