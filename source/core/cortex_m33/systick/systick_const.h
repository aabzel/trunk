#ifndef SYSTICK_GENERAL_CONST_H
#define SYSTICK_GENERAL_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#define SYSTICK_MAX_VAL 0x00FFFFFF

typedef enum{
    CLK_SRC_EXT=0,
    CLK_SRC_PROC=1,
}ClkSrc_t;

#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_GENERAL_CONST_H*/
