#ifndef BOARD_INIT_H
#define BOARD_INIT_H


#ifdef HAS_AT_START_F437
#include "at_start_f437.h"
#define AT_START_F437_INIT   {.init_function=at_start_f437_init, .name="AtStartF437",},
#else
#define AT_START_F437_INIT
#endif

#ifdef HAS_TERA_TEST
#include "board_custom.h"
#define TERA_TEST_INIT   {.init_function=tera_test_init, .name="TeraTest",},
#else
#define TERA_TEST_INIT
#endif

#ifdef HAS_FC7300_DEMO_BOARD
#include "fc7300_demo_board.h"
#define FC7300_DEMO_BOARD_INIT   {.init_function=fc7300_demo_board_init, .name="Fc7300DemoBoard",},
#else
#define FC7300_DEMO_BOARD_INIT
#endif

/*Order matters*/
#define BOARD_INIT               \
    FC7300_DEMO_BOARD_INIT               \
    TERA_TEST_INIT               \
    AT_START_F437_INIT



#endif /*BOARD_INIT_H*/
