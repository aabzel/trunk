#ifndef SPI_CUSTOM_COMMANDS_H
#define SPI_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/


#ifndef HAS_SPI_COMMANDS
#error "+HAS_SPI_COMMANDS"
#endif /*HAS_SPI_COMMANDS*/


#define SPI_CUSTOM_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_COMMANDS_H */
