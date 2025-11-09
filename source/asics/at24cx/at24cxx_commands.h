#ifndef AT24CXX_COMMANDS_H
#define AT24CXX_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_AT24CXX
#error "+ HAS_AT24CXX"
#endif

#ifndef HAS_AT24CXX_COMMANDS
#error "+ HAS_AT24CXX_COMMANDS"
#endif


#ifdef HAS_AT24CXX_WRITE
bool at24cxx_erase_command(int32_t argc, char* argv[]);
bool at24cxx_erase_chip_command(int32_t argc, char* argv[]);
bool at24cxx_write_command(int32_t argc, char* argv[]);
bool at24cxx_write_pattern_command(int32_t argc, char* argv[]);
bool at24cxx_write_byte_command(int32_t argc, char* argv[]);
bool at24cxx_write_ctrl_command(int32_t argc, char* argv[]);

#define AT24CXX_WRITE_COMMANDS                                                                           \
        SHELL_CMD("at24cxx_write_byte", "atwb", at24cxx_write_byte_command, "At24cxxWriteByte"),         \
        SHELL_CMD("at24cxx_write", "atw", at24cxx_write_command, "At24cxxWrite"),                        \
        SHELL_CMD("at24cxx_write_pattern", "atp", at24cxx_write_pattern_command, "At24cxxWritePattern"), \
        SHELL_CMD("at24cxx_write_ctrl", "atc", at24cxx_write_ctrl_command, "At24cxxWriteCtrl"),          \
        SHELL_CMD("at24cxx_erase", "ate", at24cxx_erase_command, "At24cxxErase"),                        \
        SHELL_CMD("at24cxx_erase_chip", "ata", at24cxx_erase_chip_command, "At24cxxEraseChip"),

#else
#define AT24CXX_WRITE_COMMANDS
#endif

bool at24cxx_read_command(int32_t argc, char* argv[]);
bool at24cxx_read_byte_command(int32_t argc, char* argv[]);

#define AT24CXX_READ_COMMANDS                                                                          \
        SHELL_CMD("at24cxx_read", "atr", at24cxx_read_command, "At24cxxRead"),                         \
        SHELL_CMD("at24cxx_read_byte", "atrb", at24cxx_read_byte_command, "At24cxxReadByte"),


bool at24cxx_diag_command(int32_t argc, char* argv[]);
bool at24cxx_init_command(int32_t argc, char* argv[]);


#define AT24CXX_COMMANDS                                                         \
        AT24CXX_READ_COMMANDS                                                    \
	    AT24CXX_WRITE_COMMANDS                                                   \
        SHELL_CMD("at24cxx_diag", "atd", at24cxx_diag_command, "At24cxxDiag"),   \
        SHELL_CMD("at24cxx_init", "ati", at24cxx_init_command, "At24cxxInit"),

#ifdef __cplusplus
}
#endif

#endif /* AT24CXX_COMMANDS_H */

