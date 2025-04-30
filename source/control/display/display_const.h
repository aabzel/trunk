#ifndef DISPLAY_CONST_H
#define DISPLAY_CONST_H

#include "time_mcal.h"

#define FRAME_BUFFER_SIZE 1024
#define DISPLAY_NAME_SIZE 20
#define DISPLAY_PERIOD_US SEC_2_USEC(2)

typedef enum {
    DISPLAY_PAGE_0 = 0,
    DISPLAY_PAGE_1 = 1,
    DISPLAY_PAGE_2 = 2,
    DISPLAY_PAGE_3 = 3,
    DISPLAY_PAGE_4 = 4,
    DISPLAY_PAGE_5 = 5,
    DISPLAY_PAGE_6 = 6,
    DISPLAY_PAGE_7 = 7,

    DISPLAY_PAGE_UNDEF = 8,
} DisplayPage_t;


#endif /* DISPLAY_CONST_H */
