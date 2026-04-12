#ifndef DAC_CUSTOM_COMMANDS_H
#define DAC_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


bool dac_diag_custom_command(int32_t argc, char* argv[]);
bool dac_all_int_command(int32_t argc, char* argv[]);
bool dac_data_send_command(int32_t argc, char* argv[]);
bool dac_raw_reg_command(int32_t argc, char* argv[]);
bool dac_div_command(int32_t argc, char* argv[]);


#define DAC_CUSTOM_COMMANDS                                                                       \
    SHELL_CMD("dac_div", "dacdi", dac_div_command, "DacDiv"),                          \
    SHELL_CMD("dac_all_int", "dacai", dac_all_int_command, "DacAllInt"),                          \
    SHELL_CMD("dac_raw_reg", "dacra", dac_raw_reg_command, "DacRawReg"),                          \
    SHELL_CMD("dac_diag_custom", "dacdc", dac_diag_custom_command, "DacDiagCustom"),              \
    SHELL_CMD("dac_data_send", "dacds", dac_data_send_command, "DacDataSend"),

#ifdef __cplusplus
}
#endif

#endif /* DAC_CUSTOM_COMMANDS_H */
