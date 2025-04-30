#ifndef BOARD_PARAMS_H
#define BOARD_PARAMS_H

//#include "c_defines_generated.h"

#ifdef HAS_BOARD_CUSTOM

#ifdef HAS_ERA_3_14_1
#include "era_3_14_1_params.h"
#else/*HAS_ERA_3_14_1*/
#define PAR_IDS_ERA_3_14_1
#endif/*HAS_ERA_3_14_1*/

#ifdef HAS_TERA_TEST
#include "tera_test_params.h"
#else/*HAS_TERA_TEST*/
#define PAR_IDS_TERA_TEST
#endif/*HAS_TERA_TEST*/

#ifdef HAS_AT_START
#include "at_start_params.h"
#else /*HAS_AT_START*/
#define PAR_IDS_AT_START
#endif/*HAS_AT_START*/

#define PAR_IDS_BOARD      \
    PAR_IDS_AT_START       \
    PAR_IDS_ERA_3_14_1     \
    PAR_IDS_TERA_TEST

#else /*HAS_BOARD_CUSTOM*/
#define PAR_IDS_BOARD
#endif /*HAS_BOARD_CUSTOM*/

#define BOARD_PARAMS

#endif /* BOARD_PARAMS_H */
