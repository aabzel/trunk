#ifndef UART_DIAG_H
#define UART_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "uart_types.h"

#ifdef HAS_UART_CUSTOM
#include "uart_custom_diag.h"
#endif

bool uart_diag(void);
bool uart_raw_reg_diag(uint8_t num);
bool UartDiagConfig(const UartConfig_t* const Config);
const char* uart_error2str(RxUartError_t e);
const char* UartConfigToStr(const UartConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* UART_DIAG_H */
