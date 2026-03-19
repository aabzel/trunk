#ifndef UART_CUSTOM_DIAG_H
#define UART_CUSTOM_DIAG_H

#include "mcal_types.h"
#include "uart_custom_types.h"

extern const Reg32_t UartRegs[];

uint32_t uart_reg_cnt(void);
const char* UartInfoToStr(const UartInfo_t* const Info) ;

#endif /* UART_CUSTOM_DIAG_H */


