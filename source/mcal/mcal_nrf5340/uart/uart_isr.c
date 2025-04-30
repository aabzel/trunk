#include "uart_isr.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "hal_nrfx_diag.h"
#include "nrfx_uarte.h"
#include "uart_custom_drv.h"

#ifdef HAS_CLI
#include "cli_config.h"
#include "string_reader.h"
#endif

#ifdef HAS_BT1026
#include "bt1026_config.h"
#endif /*HAS_BT1026*/

#include "log.h"
#include "uart_mcal.h"


static bool ProcNrfxUartEventHandler(UartHandle_t* UartNode, nrfx_uarte_event_t const* p_event) {
    bool res = false;
    if(UartNode) {
        UartNode->in_progress = false;
        if(p_event) {
            switch(p_event->type) {
            case NRFX_UARTE_EVT_TX_DONE:
                UartNode->tx_cnt++;
                if(0 < p_event->data.rxtx.bytes) {
                    UartNode->tx_done = true;
                    UartNode->tx_bytes += p_event->data.rxtx.bytes;
                    UartNode->cnt.byte_tx++;
                    res = true;
                }
                break;
            case NRFX_UARTE_EVT_RX_DONE:
                UartNode->rx_cnt++;
                UartNode->cnt.byte_rx++;
                UartNode->rx_done = true;
                UartNode->rx_bytes += p_event->data.rxtx.bytes;
#ifdef HAS_BT1026
                if(Bt1026Config.uart_num == UartNode->num) {
                    char rx_byte = 0;
                    uint32_t i = 0;
                    for(i = 0; i < p_event->data.rxtx.bytes; i++) {
                        if(p_event->data.rxtx.p_data) {
                            if(&p_event->data.rxtx.p_data[i]){
                                rx_byte = p_event->data.rxtx.p_data[i];
                                bool res = fifo_push(&UartNode->RxFifo, rx_byte);
                                if(false == res) {
                                    UartNode->RxFifo.err_cnt++;
                                }
                            }
                        }
                    }
                }
#endif /*HAS_BT1026*/
#ifdef HAS_CLI
                if(CliInstance[0].if_num== UartNode->num) {
                    char rx_byte = 0;
                    uint32_t i = 0;
                    for(i = 0; i < p_event->data.rxtx.bytes; i++) {
                        if(p_event->data.rxtx.p_data) {
                            if(&p_event->data.rxtx.p_data[i]){
                                rx_byte = p_event->data.rxtx.p_data[i];
                                string_reader_rx_callback(&CliInstance[0].Reader, rx_byte);
                            }
                        }
                    }
                }
#endif /*HAS_CLI*/
                res = uart_read(UartNode->num, &UartNode->rx_byte_it, 1);
                break; ///< Requested RX transfer completed.
            case NRFX_UARTE_EVT_ERROR:
                UartNode->error_cnt++;
                res = false;
                break; ///< Error reported by UART peripheral.
            }
        }
    }
    return res;
}

#ifdef NRFX_UARTE0_ENABLED
void nrfx_uart0_event_handler(nrfx_uarte_event_t const* p_event, void* p_context) {
    UartHandle_t* UartNode = UartGetNode(0);
    if(UartNode) {
        ProcNrfxUartEventHandler(UartNode, p_event);
    }
}
#endif

#ifdef NRFX_UARTE1_ENABLED
void nrfx_uart1_event_handler(nrfx_uarte_event_t const* p_event, void* p_context) {
    UartHandle_t* UartNode = UartGetNode(1);
    if(UartNode) {
        ProcNrfxUartEventHandler(UartNode, p_event);
    }
}
#endif

#ifdef NRFX_UARTE2_ENABLED
void nrfx_uart2_event_handler(nrfx_uarte_event_t const* p_event, void* p_context) {
    UartHandle_t* UartNode = UartGetNode(2);
    if(UartNode) {
        ProcNrfxUartEventHandler(UartNode, p_event);
    }
}
#endif

#ifdef NRFX_UARTE3_ENABLED
void nrfx_uart3_event_handler(nrfx_uarte_event_t const* p_event, void* p_context) {
    UartHandle_t* UartNode = UartGetNode(3);
    if(UartNode) {
        ProcNrfxUartEventHandler(UartNode, p_event);
    }
}
#endif

bool uart_interupts_enable(uint8_t uart_num) {
    bool res = false;
    switch(uart_num) {
#ifdef NRFX_UARTE0_ENABLED
    case 0:
        NVIC_SetPriority(SPIM0_SPIS0_TWIM0_TWIS0_UARTE0_IRQn, 7);
        NVIC_EnableIRQ(SPIM0_SPIS0_TWIM0_TWIS0_UARTE0_IRQn);
        break;
#endif
#ifdef NRFX_UARTE1_ENABLED
    case 1:
        NVIC_SetPriority(SPIM1_SPIS1_TWIM1_TWIS1_UARTE1_IRQn, 7);
        NVIC_EnableIRQ(SPIM1_SPIS1_TWIM1_TWIS1_UARTE1_IRQn);
        break;
#endif
#ifdef NRFX_UARTE2_ENABLED
    case 2:
        NVIC_SetPriority(SPIM2_SPIS2_TWIM2_TWIS2_UARTE2_IRQn, 7);
        NVIC_EnableIRQ(SPIM2_SPIS2_TWIM2_TWIS2_UARTE2_IRQn);
        break;
#endif /*NRF_UARTE2_NS_BASE*/

#ifdef NRFX_UARTE3_ENABLED
    case 3:
        NVIC_SetPriority(SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQn, 7);
        NVIC_EnableIRQ(SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQn);
        break;
#endif /*NRF_UARTE3_NS_BASE*/
    default:
        res = false;
        break;
    }
    return res;
}

static const UartEventHandler_t UartEventHandlerLut[] = {
#ifdef NRFX_UARTE0_ENABLED
    {
        .uart_num = 0,
        .event_handler = nrfx_uart0_event_handler,
        .valid = true,
    },
#endif
#ifdef NRFX_UARTE1_ENABLED
    {
        .uart_num = 1,
        .event_handler = nrfx_uart1_event_handler,
        .valid = true,
    },
#endif
#ifdef NRFX_UARTE2_ENABLED
    {
        .uart_num = 2,
        .event_handler = nrfx_uart2_event_handler,
        .valid = true,
    },
#endif
#ifdef NRFX_UARTE3_ENABLED
    {
        .uart_num = 3,
        .event_handler = nrfx_uart3_event_handler,
        .valid = true,
    }
#endif
};


nrfx_uarte_event_handler_t UartNum2EventHandler(uint8_t uart_num) {
    nrfx_uarte_event_handler_t event_handler = NULL;
    uint32_t cnt = ARRAY_SIZE(UartEventHandlerLut);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(UartEventHandlerLut[i].valid) {
            if(UartEventHandlerLut[i].uart_num == uart_num) {
                event_handler = UartEventHandlerLut[i].event_handler;
                break;
            }
        }
    }
    return event_handler;
}




