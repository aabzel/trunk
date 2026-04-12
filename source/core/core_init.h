#ifndef CORE_INIT_H
#define CORE_INIT_H

#ifdef HAS_CORE
#include "core_driver.h"
#else
#define CORE_MCAL_INIT
#endif

#define CORE_INIT         \
     CORE_MCAL_INIT


#endif /* CORE_INIT_H */
