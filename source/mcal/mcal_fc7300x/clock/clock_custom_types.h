#ifndef CLOCK_CUSTOM_TYPES_H
#define CLOCK_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "clock_custom_const.h"
#include "microcontroller_types.h"
#include "module_driver_csc.h"
#include "module_driver_scg.h"

typedef struct {
    uint32_t* CLOCKx;
    bool valid;
}ClockInfo_t;

/*
  CSC-CPU System Control
 */
typedef struct {
    CSC0_ClkSrcType clk_src_type;
    char* name;
    bool valid;
}ClockSourceInfo_t;

/*
  SCG - System Clock Generator
 */
typedef struct {
    SCG_ClkSrcType clk_src_type;
    char* name;
    bool valid;
}ClockSCGSourceInfo_t;




#define CLOCK_CUSTOM_TYPES     uint32_t* CLOCKx;



#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_TYPES_H
