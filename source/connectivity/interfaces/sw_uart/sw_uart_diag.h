#ifndef SW_UART_DIAG_H
#define SW_UART_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_uart_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_SW_UART
#error "+HAS_SW_UART"
#endif

#ifndef HAS_SW_UART_DIAG
#error "+HAS_SW_UART_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif


bool sw_uart_diag_one(uint8_t num);
bool sw_uart_diag(void);
const char* SwUartConfigTxToStr(const SwUartConfig_t* const Config) ;
const char* SwUartParityAlgoToStr(const SwUartParity_t parity) ;
const char* SwUartRxFrameToStr(const SwUartRxFrameState_t rx_frame_state);
const char* SwUartFrameToStr(const SwUartFrameRx_t RxFrame);
const char* SwUartNodeToStr(const SwUartHandle_t* const Node);
const char* SwUartConfigToStr(const SwUartConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* SW_UART_DIAG_H  */
