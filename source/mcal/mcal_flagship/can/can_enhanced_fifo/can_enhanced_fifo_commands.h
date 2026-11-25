#ifndef CAN_ENHANCED_FIFO_COMMANDS_H
#define CAN_ENHANCED_FIFO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool can_diag_enhanced_fifo_parse_command(int32_t argc, char* argv[]);
bool can_diag_enhanced_fifo_mem_command(int32_t argc, char* argv[]);
bool can_diag_enhanced_fifo_filter_command(int32_t argc, char* argv[]);
bool can_ext_id_check_command(int32_t argc, char* argv[]);
bool can_std_id_check_command(int32_t argc, char* argv[]);
bool can_filter_ctrl_command(int32_t argc, char* argv[]);

#define CAN_CUSTOM_ENHANCED_FIFO_COMMANDS                                                                        \
    SHELL_CMD("can_filter_ctrl", "cfic", can_filter_ctrl_command, "CanFilterCtrl"),                               \
    SHELL_CMD("can_ext_id_check", "ceic", can_ext_id_check_command, "CanExtIdCheck"),                            \
    SHELL_CMD("can_std_id_check", "csic", can_std_id_check_command, "CanStdIdCheck"),                            \
    SHELL_CMD("can_diag_enh_fifo_filter", "cdef", can_diag_enhanced_fifo_filter_command, "CanEnhancedFifoFiltes"),    \
    SHELL_CMD("can_diag_enh_fifo_parse", "cdefp", can_diag_enhanced_fifo_parse_command, "CanDiagEnhancedFiFoParce"),  \
    SHELL_CMD("can_diag_enh_fifo_mem", "cdefm", can_diag_enhanced_fifo_mem_command, "CanDiagEnhancedFiFoMem"),






#ifdef __cplusplus
}
#endif

#endif /* CAN_ENHANCED_FIFO_COMMANDS_H */
