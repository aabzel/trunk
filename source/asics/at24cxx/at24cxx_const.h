#ifndef AT24CXX_CONST_H
#define AT24CXX_CONST_H

#include "at24cxx_dep.h"
#include "time_mcal.h"

#define AT24CXX_PERIOD_US SEC_2_USEC(30)
#define AT24C02_PAGE_SIZE 8

#define AT24CXX_CHIP_ID_MASK 0xA0
#define AT24CXX_PAGE_BUFFER_SIZE 256
#define AT24CXX_PAGE_BUFFER_SIZE 256

typedef enum {
    AT24C02 = 1, /*Huaguan Semiconductor Co,Ltd */
    AT24C04 = 2, /*Huaguan Semiconductor Co,Ltd */
    AT24C08 = 3, /*Huaguan Semiconductor Co,Ltd */
    AT24C16 = 4, /*Huaguan Semiconductor Co,Ltd */

    AT24C32 = 5,
    AT24C64 = 6,
    AT24C128 = 7,
    AT24C256 = 8,
    AT24C512 = 9,
    AT24CM01 = 10,
    AT24CM02 = 11,

    AT24CXX_UNDEF = 0,
} At24cChipModel_t;

#endif /* AT24CXX_CONST_H */
