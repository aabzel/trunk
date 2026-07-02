#ifndef I2S_STM_CUSTOM_COMMANDS_H
#define I2S_STM_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

bool i2s_stm_dma_pause_command(int32_t argc, char* argv[]);
bool i2s_stm_dma_resume_command(int32_t argc, char* argv[]);
bool i2s_stm_dma_stop_command(int32_t argc, char* argv[]);
bool i2s_stm_play_command(int32_t argc, char* argv[]);
bool i2s_stm_diag_command(int32_t argc, char* argv[]);
bool i2s_stm_diag_ll_command(int32_t argc, char* argv[]);
bool i2s_stm_diag_sample_command(int32_t argc, char* argv[]);
bool i2s_stm_set_dac_command(int32_t argc, char* argv[]);
bool i2s_stm_set_iir_command(int32_t argc, char* argv[]);
bool i2s_stm_set_play_command(int32_t argc, char* argv[]);
bool i2s_stm_set_loopback_command(int32_t argc, char* argv[]);
bool i2s_stm_set_echo_command(int32_t argc, char* argv[]);
bool i2s_stm_init_command(int32_t argc, char* argv[]);
bool i2s_stm_read_write_command(int32_t argc, char* argv[]);
bool i2s_stm_read_command(int32_t argc, char* argv[]);
bool i2s_stm_read_sample_command(int32_t argc, char* argv[]);
bool i2s_stm_write_command(int32_t argc, char* argv[]);
bool i2s_stm_write_command(int32_t argc, char* argv[]);

#define I2S_STM_DIAG_COMMANDS                                                                                          \
    SHELL_CMD("i2s_diag", "i2sd", i2s_stm_diag_command, "I2sDiag"),                                                        \
        SHELL_CMD("i2s_diag_ll", "i2sdl", i2s_stm_diag_ll_command, "I2sDiagLowLevel"),                                     \
        SHELL_CMD("i2s_diag_sample", "i2sa", i2s_stm_diag_sample_command, "I2sDiagSample"),

#define I2S_STM_COMMANDS                                                                                               \
    I2S_STM_DIAG_COMMANDS                                                                                              \
    SHELL_CMD("i2s_iir", "i2sii", i2s_stm_set_iir_command, "I2sIrr"),                                                      \
        SHELL_CMD("i2s_dma_pause", "i2sdp", i2s_stm_dma_pause_command, "I2sDmaPause"),                                     \
        SHELL_CMD("i2s_dma_stop", "i2sds", i2s_stm_dma_stop_command, "I2sDmaStop"),                                        \
        SHELL_CMD("i2s_dma_resume", "i2sdr", i2s_stm_dma_resume_command, "I2sDmaResume"),                                  \
        SHELL_CMD("i2s_iir", "i2sp", i2s_stm_set_play_command, "I2sPlay"),                                                 \
        SHELL_CMD("i2s_play", "i2spl", i2s_stm_play_command, "I2sSetPlay"),                                                \
        SHELL_CMD("i2s_dac", "i2sdac", i2s_stm_set_dac_command, "I2sSetDac"),                                              \
        SHELL_CMD("i2s_echo", "i2se", i2s_stm_set_echo_command, "I2sEcho"),                                                \
        SHELL_CMD("i2s_loop", "i2sl", i2s_stm_set_loopback_command, "I2sLoopBack"),                                        \
        SHELL_CMD("i2s_TxRx", "i2srw", i2s_stm_read_write_command, "I2sReadWrite"),                                        \
        SHELL_CMD("i2s_write", "i2sw", i2s_stm_write_command, "I2sWriteHexStr"),                                           \
        SHELL_CMD("i2s_init", "i2si", i2s_stm_init_command, "I2sInit"),                                                    \
        SHELL_CMD("i2s_read", "i2sr", i2s_stm_read_command, "I2sRead "),                                                   \
        SHELL_CMD("i2s_read_sample", "i2srs", i2s_stm_read_sample_command, "I2sReadSample "),

#ifdef __cplusplus
}
#endif

#endif /* I2S_STM_CUSTOM_COMMANDS_H */
