#ifndef DUMMY_MCU_DIAG_H
#define DUMMY_MCU_DIAG_H

#include "std_includes.h"


#ifdef HAS_INTERRUPT
#include "interrupt_types.h"

extern const IntNumInfo_t IntNumInfo[];
uint32_t interrupt_info_get_cnt(void);

#endif




#endif /* DUMMY_MCU_DIAG_H */
