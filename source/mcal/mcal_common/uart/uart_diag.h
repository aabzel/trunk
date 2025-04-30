#ifndef UART_DIAG_H
#define UART_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "uart_types.h"

const char* uart_error2str(RxUartError_t e);

#ifdef __cplusplus
}
#endif

#endif /* UART_DIAG_H */
