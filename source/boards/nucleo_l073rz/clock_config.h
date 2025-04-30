#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include <stdbool.h>

#define HSE_VALUE 8000000U /*!< Value of the External oscillator in Hz */

bool clock_init(void);


#endif /* CLOCK_CONFIG_H  */
