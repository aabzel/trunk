#ifndef SX1262_COMMANDS_H
#define SX1262_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifdef HAS_GFSK
#include "sx1262_gfsk_commands.h"
#else
#define SX1262_GFSK_COMMANDS
#endif

#ifdef HAS_LORA
#include "sx1262_lora_commands.h"
#else
#define SX1262_LORA_COMMANDS
#endif

bool sx1262_get_irq_command(int32_t argc, char* argv[]);
bool sx1262_test_command(int32_t argc, char* argv[]);
bool sx1262_clear_err_command(int32_t argc, char* argv[]);
bool sx1262_clear_fifo_command(int32_t argc, char* argv[]);
bool sx1262_diag_command(int32_t argc, char* argv[]);
bool sx1262_init_command(int32_t argc, char* argv[]);
bool sx1262_int_diag_command(int32_t argc, char* argv[]);
bool sx1262_read_fifo_command(int32_t argc, char* argv[]);
bool sx1262_read_reg_command(int32_t argc, char* argv[]);
bool sx1262_read_rx_payload_command(int32_t argc, char* argv[]);
bool sx1262_reg_map_command(int32_t argc, char* argv[]);
bool sx1262_reset_command(int32_t argc, char* argv[]);
bool sx1262_rx_command(int32_t argc, char* argv[]);
bool sx1262_statistic_command(int32_t argc, char* argv[]);
bool sx1262_send_opcode_command(int32_t argc, char* argv[]);
bool sx1262_set_freq_command(int32_t argc, char* argv[]);
bool sx1262_set_irq_command(int32_t argc, char* argv[]);
bool sx1262_get_status_command(int32_t argc, char* argv[]);
bool sx1262_set_sync_word_command(int32_t argc, char* argv[]);
bool sx1262_sleep_command(int32_t argc, char* argv[]);
bool sx1262_tx_command(int32_t argc, char* argv[]);
bool sx1262_mute_command(int32_t argc, char* argv[]);
bool sx1262_write_reg_command(int32_t argc, char* argv[]);

#define SX1262_COMMANDS_BASE                                                                                           \
    SHELL_CMD("sx1262Diag", "sxd", sx1262_diag_command, "SX1262Diag"),                                                 \
        SHELL_CMD("sx1262_get_status", "sxgs", sx1262_get_status_command, "SX1262 GetStatus"),                         \
        SHELL_CMD("sx1262_clr_err", "sxce", sx1262_clear_err_command, "SX1262 clear errors"),                          \
        SHELL_CMD("sx1262_clr_fifo", "sxcf", sx1262_clear_fifo_command, "SX1262 clear FIFO"),                          \
        SHELL_CMD("sx1262Init", "sxi", sx1262_init_command, "SX1262 init"),                                            \
        SHELL_CMD("sx1262_stat", "sxst", sx1262_statistic_command, "SX1262 statistic"),                                \
        SHELL_CMD("sx1262_test", "sxs", sx1262_test_command, "SX1262 test"),                                           \
        SHELL_CMD("sx1262_fifo", "sxrf", sx1262_read_fifo_command, "SX1262 read FIFO"),                                \
        SHELL_CMD("sx1262_opcode", "sxo", sx1262_send_opcode_command, "SX1262 send opcode"),                           \
        SHELL_CMD("sx1262_read_rx_data", "sxrp", sx1262_read_rx_payload_command, "SX1262 read rx data"),               \
        SHELL_CMD("sx1262_reg_map", "sxm", sx1262_reg_map_command, "SX1262 reg map"),                                  \
        SHELL_CMD("sx1262_mute", "sxu", sx1262_mute_command, "SX1262 mute"),                                           \
        SHELL_CMD("sx1262_reg_rd", "sxrr", sx1262_read_reg_command, "SX1262 read reg"),                                \
        SHELL_CMD("sx1262_reg_wr", "sxwr", sx1262_write_reg_command, "SX1262 write reg"),                              \
        SHELL_CMD("sx1262_reset", "sxrt", sx1262_reset_command, "SX1262 reset"),                                       \
        SHELL_CMD("sx1262_rx", "sxr", sx1262_rx_command, "SX1262 receive"),                                            \
        SHELL_CMD("sx1262_set_freq", "sxsf", sx1262_set_freq_command, "SX1262 set freq"),                              \
        SHELL_CMD("sx1262_set_irq", "sxir", sx1262_set_irq_command, "SX1262 SetIRQ"),                                  \
        SHELL_CMD("sx1262_int_diag", "sxid", sx1262_int_diag_command, "SX1262 InterruptsDiag"),                        \
        SHELL_CMD("sx1262_get_irq", "sxgi", sx1262_get_irq_command, "SX1262 GetIRQ"),                                  \
        SHELL_CMD("sx1262_sleep", "sxsp", sx1262_sleep_command, "SX1262 sleep"),                                       \
        SHELL_CMD("sx1262_sync", "sxssw", sx1262_set_sync_word_command, "SX1262 set sync word"),                       \
        SHELL_CMD("sx1262_tx", "sxt", sx1262_tx_command, "SX1262 transmit"),

#ifdef HAS_SX1262_EX_DEBUG
bool sx1262_set_packet_param_command(int32_t argc, char* argv[]);
bool sx1262_calc_command(int32_t argc, char* argv[]);
bool sx1262_calc_fresnel_zone_command(int32_t argc, char* argv[]);
bool sx1262_proc_command(int32_t argc, char* argv[]);
bool sx1262_set_standby_command(int32_t argc, char* argv[]);
bool sx1262_proc_fifo_command(int32_t argc, char* argv[]);

#define SX1262_COMMANDS_DEBUG                                                                                          \
    SHELL_CMD("sx1262Proc", "sxp", sx1262_proc_command, "SX1262 proc"),                                                \
        SHELL_CMD("FresnelZone", "fz", sx1262_calc_fresnel_zone_command, "FresnelZone"),                               \
        SHELL_CMD("sx1262ProcFifo", "sxpf", sx1262_proc_fifo_command, "ProcFifo"),                                     \
        SHELL_CMD("sx1262Standby", "sxss", sx1262_set_standby_command, "SX1262 SetStandBy"),                           \
        SHELL_CMD("sx1262Calc", "sxc", sx1262_calc_command, "SX1262 calc"),

#else
#define SX1262_COMMANDS_DEBUG
#endif /*HAS_SX1262_EX_DEBUG*/

#define SX1262_COMMANDS                                                                                                \
    SX1262_LORA_COMMANDS                                                                                               \
    SX1262_GFSK_COMMANDS                                                                                               \
    SX1262_COMMANDS_BASE                                                                                               \
    SX1262_COMMANDS_DEBUG

#ifdef __cplusplus
}
#endif

#endif /* SX1262_COMMANDS_H */
