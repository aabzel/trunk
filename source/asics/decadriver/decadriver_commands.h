#ifndef DECADRIVER_COMMANDS_H
#define DECADRIVER_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif

#ifndef HAS_DECADRIVER
#error "+ HAS_DECADRIVER"
#endif

#ifndef HAS_DECADRIVER_COMMANDS
#error "+HAS_DECADRIVER_COMMANDS"
#endif


bool decadriver_diag_command(int32_t argc, char* argv[]);
bool decadriver_init_command(int32_t argc, char* argv[]);
bool decadriver_read_offset_command(int32_t argc, char* argv[]);
bool decadriver_read_rx_buff_command(int32_t argc, char* argv[]);
bool decadriver_read_register_one_command(int32_t argc, char* argv[]);
bool decadriver_reset_command(int32_t argc, char* argv[]);
bool decadriver_rx_set_command(int32_t argc, char* argv[]);
bool decadriver_rx_reset_command(int32_t argc, char* argv[]);
bool decadriver_write_tx_buff_command(int32_t argc, char* argv[]);
bool decadriver_write_reg32_command(int32_t argc, char* argv[]);
bool decadriver_tx_command(int32_t argc, char* argv[]);

#define DECADRIVER_COMMANDS                                            \
        SHELL_CMD("decadriver_diag", "ddd", decadriver_diag_command, "DecaDiag"),                                         \
        SHELL_CMD("decadriver_init", "ddi", decadriver_init_command, "DecaInit"),                                         \
        SHELL_CMD("decadriver_rx_set", "drs", decadriver_rx_set_command, "DecaRxSet"),                                    \
        SHELL_CMD("decadriver_rx_reset", "dxr", decadriver_rx_reset_command, "DecaRxReset"),                                         \
        SHELL_CMD("decadriver_read_rx_buff", "drrb", decadriver_read_rx_buff_command, "DecaReadRxBuff"),                  \
        SHELL_CMD("decadriver_read_reg", "drr1", decadriver_read_register_one_command, "DecaReadReg1"),                   \
        SHELL_CMD("decadriver_read_offset", "dro", decadriver_read_offset_command, "DecaReadOffSet"),                     \
        SHELL_CMD("decadriver_reset", "dwr", decadriver_reset_command, "DecaReset"),                                      \
        SHELL_CMD("decadriver_tx_buff", "dtb", decadriver_tx_command, "DecaTxBuff"),                                 \
        SHELL_CMD("decadriver_write_reg32", "dw32", decadriver_write_reg32_command, "DecaWriteRegister32"),               \
        SHELL_CMD("decadriver_write_tx_buff", "dwt", decadriver_write_tx_buff_command, "DecaWriteTxBuff"),

#ifdef __cplusplus
}
#endif

#endif /* DECADRIVER_COMMANDS_H */
