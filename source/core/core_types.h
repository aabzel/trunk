#ifndef CORE_TYPE_H
#define CORE_TYPE_H

#include "std_includes.h"
#include "core_const.h"

#ifdef HAS_RATIONAL_NUM
#include "rational_num_types.h"
#endif

#ifdef HAS_FLOAT
#include "float_types.h"
#endif

typedef struct{
    uint8_t core_num;
//  uint32_t vector_start;
    uint32_t reset_handler;
    uint32_t main_addr;
}CoreInfo_t;

typedef union {
    uint32_t mem[64];
    uint32_t dword[16];
    struct {
        uint32_t stack_top; /**/
        uint32_t reset_handler; /**/
        uint32_t NMI_Handler; /**/
        uint32_t HardFault_Handler; /**/
        uint32_t MemManage_Handler; /**/
        uint32_t BusFault_Handler; /**/
        uint32_t UsageFault_Handler; /**/
        uint32_t RES1[4]; /**/
        uint32_t SVC_Handler; /**/
        uint32_t DebugMon_Handler; /**/
        uint32_t RES2; /**/
        uint32_t PendSV_Handler; /**/
        uint32_t SysTick_Handler; /**/
    };
} ArmCortexVectorTable_t;


#define CORE_COMMON_VARIABLES                          \
    char* name;                                        \
    uint8_t num;                                       \
    uint32_t stack_top;                                \
    uint32_t stack_limit;                              \
    bool valid;

typedef struct {
    CORE_COMMON_VARIABLES
}CoreConfig_t;

typedef struct {
    CORE_COMMON_VARIABLES
    bool init;
    uint32_t spin;
#ifdef HAS_FLOAT
    FloatFixPoint_t stack_used;
#endif
}CoreHandle_t;

#endif /* CORE_TYPE_H */



