#ifndef I2S_CUSTOM_CUSTOM_COMMANDS_H
#define I2S_CUSTOM_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "cli_drv.h"

bool i2s_custom_dma_pause_command(int32_t argc, char* argv[]);
bool i2s_custom_dma_resume_command(int32_t argc, char* argv[]);
bool i2s_custom_dma_stop_command(int32_t argc, char* argv[]);
bool i2s_custom_play_command(int32_t argc, char* argv[]);
bool i2s_custom_diag_command(int32_t argc, char* argv[]);
bool i2s_custom_diag_ll_command(int32_t argc, char* argv[]);
bool i2s_custom_diag_sample_command(int32_t argc, char* argv[]);
bool i2s_custom_set_dac_command(int32_t argc, char* argv[]);
bool i2s_custom_set_iir_command(int32_t argc, char* argv[]);
bool i2s_custom_set_play_command(int32_t argc, char* argv[]);
bool i2s_custom_set_loopback_command(int32_t argc, char* argv[]);
bool i2s_custom_set_echo_command(int32_t argc, char* argv[]);
bool i2s_custom_init_command(int32_t argc, char* argv[]);
bool i2s_custom_read_write_command(int32_t argc, char* argv[]);
bool i2s_custom_read_command(int32_t argc, char* argv[]);
bool i2s_custom_read_sample_command(int32_t argc, char* argv[]);
bool i2s_custom_write_command(int32_t argc, char* argv[]);
bool i2s_custom_write_command(int32_t argc, char* argv[]);
bool i2s_prescaler_command(int32_t argc, char* argv[]) ;

#define I2S_CUSTOM_DIAG_COMMANDS                                                                                          \
    SHELL_CMD("i2s_diag", "i2scd", i2s_custom_diag_command, "I2sDiag"),                                                        \
    SHELL_CMD("i2s_diag_ll", "i2sdl", i2s_custom_diag_ll_command, "I2sDiagLowLevel"),                                     \

#define I2S_CUSTOM_COMMANDS                                                                                               \
    I2S_CUSTOM_DIAG_COMMANDS                                                                                              \
        SHELL_CMD("i2s_prescaler", "i2p", i2s_prescaler_command, "I2sPrescaler"),                                        \
        SHELL_CMD("i2s_read", "i2sr", i2s_custom_read_command, "I2sRead "),                                                   \

#ifdef __cplusplus
}
#endif

#endif /* I2S_CUSTOM_CUSTOM_COMMANDS_H */
