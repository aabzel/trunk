#ifndef SW_NVRAM_COMMANDS_H
#define SW_NVRAM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_SW_NVRAM
#error "+ HAS_SW_NVRAM"
#endif /*HAS_SW_NVRAM*/

#ifndef HAS_SW_NVRAM_COMMANDS
#error "+ HAS_SW_NVRAM_COMMANDS"
#endif /*HAS_SW_NVRAM_COMMANDS*/

bool sw_nvram_write_command(int32_t argc, char* argv[]);
bool sw_nvram_toggle_page_command(int32_t argc, char* argv[]);
bool sw_nvram_read_command(int32_t argc, char* argv[]);
bool sw_nvram_delete_command(int32_t argc, char* argv[]);
bool sw_nvram_init_command(int32_t argc, char* argv[]);
bool sw_nvram_diag_command(int32_t argc, char* argv[]);
bool sw_nvram_final_diag_command(int32_t argc, char* argv[]);
bool sw_nvram_capacity_command(int32_t argc, char* argv[]);
bool sw_nvram_draw_tree_command(int32_t argc, char* argv[]);

#define SW_NVRAM_COMMANDS                                                                                 \
    SHELL_CMD("sw_nvram_toggle_page", "nvro", sw_nvram_toggle_page_command, "NvRAMToggle"),               \
    SHELL_CMD("sw_nvram_final", "nvrfd", sw_nvram_final_diag_command, "NvRAMfinal"),                      \
    SHELL_CMD("sw_nvram_capacity", "nvrc", sw_nvram_capacity_command, "NvRAMCapacity"),                   \
    SHELL_CMD("sw_nvram_tree", "nvre", sw_nvram_draw_tree_command, "NvRAMTree"),                          \
    SHELL_CMD("sw_nvram_write", "nvrw", sw_nvram_write_command, "NvRAMwrite"),                            \
        SHELL_CMD("sw_nvram_read", "nvrr", sw_nvram_read_command, "NvRAMread"),                           \
        SHELL_CMD("sw_nvram_delete", "nvrt", sw_nvram_delete_command, "NvRAMdelete"),                     \
        SHELL_CMD("sw_nvram_init", "nvri", sw_nvram_init_command, "NvRAMinit"),                           \
        SHELL_CMD("sw_nvram_diag", "nvrd", sw_nvram_diag_command, "NvRAMdiag"),

#ifdef __cplusplus
}
#endif

#endif /* SW_NVRAM_COMMANDS_H */
