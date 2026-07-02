#ifndef EXT_INT_CUSTOM_TYPES_H
#define EXT_INT_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ext_int_custom_const.h"
#include "microcontroller_types.h"
#include "clock_const.h"
#include "stm32fx_hal.h"
#include "stm32fx_hal_exti.h"

#define EXT_INT_CUSTOM_VARIABLES    \
                 EXTI_HandleTypeDef h_exti;


/*
12.3.6 Pending register (EXTI_PR)
Address offset: 0x14
*/
typedef union{
    volatile uint32_t qword;
    struct {
        volatile uint32_t PR0  : 1;   /*  Pending bit for line 0   */
        volatile uint32_t PR1  : 1;   /*  Pending bit for line 1   */
        volatile uint32_t PR2  : 1;   /*  Pending bit for line 2   */
        volatile uint32_t PR3  : 1;   /*  Pending bit for line 3   */
        volatile uint32_t PR4  : 1;   /*  Pending bit for line 4   */
        volatile uint32_t PR5  : 1;   /*  Pending bit for line 5   */
        volatile uint32_t PR6  : 1;   /*  Pending bit for line 6   */
        volatile uint32_t PR7  : 1;   /*  Pending bit for line 7   */
        volatile uint32_t PR8  : 1;   /*  Pending bit for line 8   */
        volatile uint32_t PR9  : 1;   /*  Pending bit for line 9   */
        volatile uint32_t PR10 : 1;   /*  Pending bit for line 10  */
        volatile uint32_t PR11 : 1;   /*  Pending bit for line 11  */
        volatile uint32_t PR12 : 1;   /*  Pending bit for line 12  */
        volatile uint32_t PR13 : 1;   /*  Pending bit for line 13  */
        volatile uint32_t PR14 : 1;   /*  Pending bit for line 14  */
        volatile uint32_t PR15 : 1;   /*  Pending bit for line 15  */
        volatile uint32_t PR16 : 1;   /*  Pending bit for line 16  */
        volatile uint32_t PR17 : 1;   /*  Pending bit for line 17  */
        volatile uint32_t PR18 : 1;   /*  Pending bit for line 18  */
        volatile uint32_t PR19 : 1;   /*  Pending bit for line 19  */
        volatile uint32_t PR20 : 1;   /*  Pending bit for line 20  */
        volatile uint32_t PR21 : 1;   /*  Pending bit for line 21  */
        volatile uint32_t PR22 : 1;   /*  Pending bit for line 22  */
        volatile uint32_t RES1 : 9;   /*  Reserved bits 23-31      */
    } ;
}ExtIntRegPending_t;


typedef struct {
    bool valid;
    uint8_t num;
    IRQn_Type irq_n;
    uint32_t exint_line_n;
}ExtIntInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_CUSTOM_TYPES_H  */
