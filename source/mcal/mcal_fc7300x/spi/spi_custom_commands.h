#ifndef SPI_CUSTOM_COMMANDS_H
#define SPI_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

#ifndef HAS_SPI_COMMANDS
#error "+HAS_SPI_COMMANDS"
#endif /*HAS_SPI_COMMANDS*/

bool spi_diag_low_level_command(int32_t argc, char* argv[]);
bool spi_raw_reg_command(int32_t argc, char* argv[]);

#define SPI_CUSTOM_COMMANDS                                                                       \
    SHELL_CMD("spi_raw_reg", "spira", spi_raw_reg_command, "SpiRawReg"),                          \
    SHELL_CMD("spi_diag_low_level", "spidl", spi_diag_low_level_command, "SpiDiagLowLevel"),


#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_COMMANDS_H */
