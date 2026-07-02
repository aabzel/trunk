#ifndef DWT_TYPES_H
#define DWT_TYPES_H

#include "std_includes.h"
#include "dwt_const.h"
#include "microcontroller.h"

/* Table C1-24 DWT_CTRL (0xE0001000) */
typedef union{
    uint32_t dword;
    struct{
        uint32_t CYCCNTENA:1;      /*[0]  Enable CYCCNT */
        uint32_t POSTPRESET:4; /*[4:1]  Preset (reload) value for POSTCNT */
        uint32_t POSTCNT:4; /*[8:5]  xxxxxxxxxxxxxx */
        uint32_t CYCTAP:1; /*[9]  Selects a tap on the DWT_CYCCNT register */
        uint32_t SYNCTAP:2; /*[11:10]  Selects a synchronization packet rate. */
        uint32_t PCSAMPLENA:1; /*[12]  See CYCEVTENA */
        uint32_t RES1:3;// 13 14 15
        uint32_t EXCTRCENA:1; /*[16]  Enables exception trace. */
        uint32_t CPIEVTENA:1; /* [17] Enables CPI count event. */
        uint32_t EXCEVTENA:1; /*[18]  Enables Exception Overhead event */
        uint32_t SLEEPEVTENA:1; /*[19]  Enables Sleep count event. */
        uint32_t LSUEVTENA:1; /*[20]  Enables LSU count event. */
        uint32_t FOLDEVTENA:1; /*[21]  Enables Folded-instruction count event */
        uint32_t CYCEVTENA:1; /*[22]  Used with PCSAMPLENA to control CYCCNT or PC sample event generation. */
        uint32_t RES2:1; /*[23 ]  xxxxxxxxxxxxxx */
        uint32_t NOPRFCNT:1; /*[24]  When set, DWT_FOLDCNT, DWT_LSUCNT, DWT_SLEEPCNT, DWT_EXCCNT, and DWT_CPICNT are not supported */
        uint32_t NOCYCCNTd:1; /*[25]  When set, DWT_CYCCNT is not supported */
        uint32_t NOEXTTRIGc:1; /*[26]  When set, no CMPMATCH[N] support */
        uint32_t NOTRCPKTb:1; /*[27]  When set, trace sampling and exception tracing are not supported */
        uint32_t NUMCOMP:4; /*[31:28]  Number of comparators available. */
    };
}ARM_DWT_CTRL_t;

#define DWT_COMMON_VARIABLES                                                              \
    DWT_Type* DWTx; /*PHY Address. Initial  physical address of the subsystem registers*/ \
    char* name;                                                                           \
    uint32_t counter_freq;                                                                          \
    uint8_t num;                                                                          \
    bool valid;

typedef struct {
    DWT_COMMON_VARIABLES
}DwtConfig_t;

typedef struct {
    DWT_COMMON_VARIABLES
    bool init;
    uint32_t spin;
    volatile uint64_t divider_1us;
    volatile uint64_t divider_1ms;
    volatile uint64_t up_time_u64;
    volatile uint64_t wrap_counter;
    volatile uint32_t up_time_u32;
    volatile uint32_t up_time_u32_prev;
}DwtHandle_t;


#endif /* DWT_TYPES_H */
