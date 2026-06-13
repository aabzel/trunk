#ifndef POSTPONE_FUN_CONFIG_H
#define POSTPONE_FUN_CONFIG_H

#include "postpone_fun_types.h"

typedef enum{
    POST_FUN_FUN1= 1,
    POST_FUN_RESET = 2,
    POST_FUN_UNDEF = 0,
}LegalPostPoneActions_t;

extern const PostponeFunConfig_t PostponeFunConfig[];
extern PostponeFunHandle_t PostponeFunInstance[];

uint32_t postpone_fun_get_cnt(void);

#endif /* POSTPONE_FUN_CONFIG_H  */
