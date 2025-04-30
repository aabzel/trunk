#ifndef BOARD_INIT_H
#define BOARD_INIT_H


#ifdef HAS_AT_START_F437
#include "board_custom.h"
#define AT_START_F437_INIT   {.init_function=at_start_f437_init, .name="AtStartF437",},
#else
#define AT_START_F437_INIT
#endif /*HAS_AT_START_F437*/

#ifdef HAS_TERA_TEST
#include "board_custom.h"
#define TERA_TEST_INIT   {.init_function=tera_test_init, .name="TeraTest",},
#else
#define TERA_TEST_INIT
#endif /*HAS_TERA_TEST*/


/*Order matters*/
#define BOARD_INIT               \
    TERA_TEST_INIT               \
    AT_START_F437_INIT



#endif /*BOARD_INIT_H*/
