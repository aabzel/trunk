#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_SPI_CUSTOM_COMMANDS
#include "spi_custom_commands.h"
#else
#define SPI_CUSTOM_COMMANDS
#endif

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

#ifndef HAS_SPI_COMMANDS
#error "+HAS_SPI_COMMANDS"
#endif

bool spi_diag_int_command(int32_t argc, char* argv[]);
bool spi_init_command(int32_t argc, char* argv[]);
bool spi_reg_map_command(int32_t argc, char* argv[]);
bool spi_diag_command(int32_t argc, char* argv[]);
bool spi_read_command(int32_t argc, char* argv[]);
bool spi_write_command(int32_t argc, char* argv[]);
bool spi_write_read_command(int32_t argc, char* argv[]);
bool spi_move_mode_command(int32_t argc, char* argv[]);
bool spi_read_byte_command(int32_t argc, char* argv[]);
bool spi_loopback_command(int32_t argc, char* argv[]);

#define SPI_COMMANDS                                                                                               \
    SPI_CUSTOM_COMMANDS                                                                                            \
    SHELL_CMD("spi_init", "spin", spi_init_command, "SpiInit"),                                                    \
    SHELL_CMD("spi_move_mode", "spm", spi_move_mode_command, "SpiMoveMode"),                                       \
    SHELL_CMD("spi_loopback", "splb", spi_loopback_command, "SpiLoopBack"),                                        \
    SHELL_CMD("spi_diag", "spd", spi_diag_command, "SpiDiag"),                                                     \
    SHELL_CMD("spi_interrupt", "spi", spi_diag_int_command, "SpiDiagInterrupts"),                                  \
    SHELL_CMD("spi_read", "spr", spi_read_command, "SpiRead"),                                                     \
    SHELL_CMD("spi_read_byte", "sprb", spi_read_byte_command, "SpiReadByte"),                                      \
    SHELL_CMD("spi_write", "spw", spi_write_command, "SpiWrite"),                                                  \
    SHELL_CMD("spi_write_read", "spwr", spi_write_read_command, "SpiWriteRead"),                                   \
    SHELL_CMD("spi_reg_map", "srm", spi_reg_map_command, "SpiRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* SPI_COMMANDS_H */
