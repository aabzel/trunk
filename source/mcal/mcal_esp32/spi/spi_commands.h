#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool spi_diag_int_command(int32_t argc, char* argv[]);
bool spi_diag_command(int32_t argc, char* argv[]);
bool spi_read_command(int32_t argc, char* argv[]);
bool spi_write_command(int32_t argc, char* argv[]);

#define SPI_COMMANDS                                                                                                   \
    SHELL_CMD("spi_diag", "sd", spi_diag_command, "SPI diag"),                                                         \
        SHELL_CMD("spi_interrupt", "sdi", spi_diag_int_command, "SPI diag interrupts"),                                \
        SHELL_CMD("spi_read", "sr", spi_read_command, "SPI read"),                                                     \
        SHELL_CMD("spi_write", "sw", spi_write_command, "SPI write hex str"),

#ifdef __cplusplus
}
#endif

#endif /* SPI_COMMANDS_H */
