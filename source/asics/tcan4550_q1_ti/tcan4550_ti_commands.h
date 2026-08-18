#ifndef TCAN4550_TI_COMMANDS_H
#define TCAN4550_TI_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cli_drv.h"

bool tcan4550_ti_clear_mram_command(int32_t argc, char* argv[]);
bool tcan4550_ti_init_command(int32_t argc, char* argv[]);
bool tcan4550_ti_read_command(int32_t argc, char* argv[]);
bool tcan4550_ti_read_reg_command(int32_t argc, char* argv[]);
bool tcan4550_ti_send_frame_command(int32_t argc, char* argv[]);
bool tcan4550_ti_set_mode_command(int32_t argc, char* argv[]);
bool tcan4550_ti_write_reg_command(int32_t argc, char* argv[]);

#define TCAN4550_TI_TI_COMMANDS                                                                                        \
    SHELL_CMD("tcan4550_ti_send", "tcs", tcan4550_ti_send_frame_command, "TCAN4550 send"),                             \
        SHELL_CMD("tcan4550_ti_set_mode", "tcsm", tcan4550_ti_set_mode_command, "TCAN4550 set mode"),                  \
        SHELL_CMD("tcan4550_ti_init", "tci", tcan4550_ti_init_command, "TCAN4550 init"),                               \
        SHELL_CMD("tcan4550_ti_read", "tcr", tcan4550_ti_read_command, "TCAN4550 read"),                               \
        SHELL_CMD("tcan4550_ti_clr_mram", "tccm", tcan4550_ti_clear_mram_command, "TCAN4550 clear MRAM"),              \
        SHELL_CMD("tcan4550_ti_read_reg", "tcrr", tcan4550_ti_read_reg_command, "TCAN4550 read reg"),                  \
        SHELL_CMD("tcan4550_ti_reg_wr", "tcwr", tcan4550_ti_write_reg_command, "TCAN4550 write reg"),

#ifdef __cplusplus
}
#endif

#endif /* TCAN4550_TI_COMMANDS_H  */
