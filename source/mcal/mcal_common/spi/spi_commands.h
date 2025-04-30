#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

#ifndef HAS_SPI_COMMANDS
#error "+HAS_SPI_COMMANDS"
#endif

bool spi_diag_int_command(int32_t argc, char* argv[]);
bool spi_init_command(int32_t argc, char* argv[]);
bool spi_diag_command(int32_t argc, char* argv[]);
bool spi_read_command(int32_t argc, char* argv[]);
bool spi_write_command(int32_t argc, char* argv[]);

#define SPI_COMMANDS                                                                                                   \
    SHELL_CMD("spi_init", "spin", spi_init_command, "SpiInit"),                                                        \
        SHELL_CMD("spi_diag", "spd", spi_diag_command, "Spi diag"),                                                    \
        SHELL_CMD("spi_interrupt", "spi", spi_diag_int_command, "Spi diag interrupts"),                                \
        SHELL_CMD("spi_read", "spr", spi_read_command, "Spi read"),                                                    \
        SHELL_CMD("spi_write", "spw", spi_write_command, "Spi write hex str"),

#ifdef __cplusplus
}
#endif

#endif /* SPI_COMMANDS_H */
