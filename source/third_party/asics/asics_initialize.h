#ifndef ASICS_INITIALIZE_H
#define ASICS_INITIALIZE_H

#include "std_includes.h"

#ifdef HAS_LIS3DH_EHAL
#include "lis3dh_driver.h"
bool lis3dh_init(void);

#define LIS3DH_INITIALIZE {.init_function = lis3dh_init, .name="TpLIS3DH",},
#else /*HAS_LIS3DH*/
#define LIS3DH_INITIALIZE
#endif /*HAS_LIS3DH*/

#ifdef HAS_NAU8814_EHAL
#include "nau8814_driver.h"
bool nau8814_init(void);

#define NAU8814_INITIALIZE {.init_function=nau8814_init, .name="TpNau8814",},
#else /*HAS_NAU8814*/
#define NAU8814_INITIALIZE
#endif /*HAS_NAU8814*/

#define ASICS_INITIALIZE                \
    LIS3DH_INITIALIZE                  \
    NAU8814_INITIALIZE

#endif /* ASICS_INITIALIZE_H */
