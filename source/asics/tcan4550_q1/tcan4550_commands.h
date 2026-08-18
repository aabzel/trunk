#ifndef TCAN4550_COMMANDS_H
#define TCAN4550_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cli_drv.h"

bool tcan4550_clear_mram_command(int32_t argc, char* argv[]);
bool tcan4550_deinit_command(int32_t argc, char* argv[]);
bool tcan4550_diag_hl_command(int32_t argc, char* argv[]);
bool tcan4550_diag_ll_command(int32_t argc, char* argv[]);
bool tcan4550_diag_mram_command(int32_t argc, char* argv[]);
bool tcan4550_fifo_diag_command(int32_t argc, char* argv[]);
bool tcan4550_get_fifos_command(int32_t argc, char* argv[]);
bool tcan4550_init_command(int32_t argc, char* argv[]);
bool tcan4550_int_diag_command(int32_t argc, char* argv[]);
bool tcan4550_read_command(int32_t argc, char* argv[]);
bool tcan4550_read_reg_command(int32_t argc, char* argv[]);
bool tcan4550_reg_map_command(int32_t argc, char* argv[]);
bool tcan4550_reset_command(int32_t argc, char* argv[]);
bool tcan4550_send_std_frame_command(int32_t argc, char* argv[]);
bool tcan4550_send_ext_frame_command(int32_t argc, char* argv[]);
bool tcan4550_set_lock_command(int32_t argc, char* argv[]);
bool tcan4550_set_mode_command(int32_t argc, char* argv[]);
bool tcan4550_set_rate_command(int32_t argc, char* argv[]);
bool tcan4550_write_reg_command(int32_t argc, char* argv[]);

#define TCAN4550_COMMANDS                                                                                               \
        SHELL_CMD("tcan4550_send_std", "css", tcan4550_send_std_frame_command, "TCAN4550 send std frame"),                  \
        SHELL_CMD("tcan4550_send_ext", "cse", tcan4550_send_ext_frame_command, "TCAN4550 send ext frame"),                  \
        SHELL_CMD("tcan4550_diag_ll", "cdl", tcan4550_diag_ll_command, "TCAN4550 diag low level"),                      \
        SHELL_CMD("tcan4550_set_mode", "csm", tcan4550_set_mode_command, "TCAN4550 set mode"),                      \
        SHELL_CMD("tcan4550_set_rate", "csr", tcan4550_set_rate_command, "TCAN4550 set rate"),                      \
        SHELL_CMD("tcan4550_set_lock", "csl", tcan4550_set_lock_command, "TCAN4550 set lock"),                      \
        SHELL_CMD("tcan4550_diag_hl", "cdh", tcan4550_diag_hl_command, "TCAN4550 diag hight level"),                \
        SHELL_CMD("tcan4550_diag_ram", "cdr", tcan4550_diag_mram_command, "TCAN4550 diag MRAM"),                    \
        SHELL_CMD("tcan4550_init", "ci", tcan4550_init_command, "TCAN4550 init"),                                       \
        SHELL_CMD("tcan4550_deinit", "cdi", tcan4550_deinit_command, "TCAN4550 deinit"),                                       \
        SHELL_CMD("tcan4550_fifo_diag", "cfd", tcan4550_fifo_diag_command, "TCAN4550 FIFO diag"),                       \
        SHELL_CMD("tcan4550_fifo_get", "cfg", tcan4550_get_fifos_command, "TCAN4550 get from fifos"),                   \
        SHELL_CMD("tcan4550_reg_map", "cm", tcan4550_reg_map_command, "TCAN4550 reg map"),                              \
        SHELL_CMD("tcan4550_read", "cr", tcan4550_read_command, "TCAN4550 read"),                                       \
        SHELL_CMD("tcan4550_clr_mram", "ccm", tcan4550_clear_mram_command, "TCAN4550 clear MRAM"),                      \
        SHELL_CMD("tcan4550_read_reg", "crr", tcan4550_read_reg_command, "TCAN4550 read reg"),                          \
        SHELL_CMD("tcan4550_reset", "crt", tcan4550_reset_command, "TCAN4550 reset"),                                   \
        SHELL_CMD("tcan4550_reg_wr", "cwr", tcan4550_write_reg_command, "TCAN4550 write reg"),                          \


#ifdef __cplusplus
}
#endif

#endif /* TCAN4550_COMMANDS_H  */
