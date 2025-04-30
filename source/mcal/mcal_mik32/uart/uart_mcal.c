#include "uart_mcal.h"

#ifdef HAS_LOG
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifdef HAS_BIT_UTILS
#include "bit_utils.h"
#endif

#include "code_generator.h"
#include "hal_diag.h"
#include "hal_mcal.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "mik32_hal_irq.h"
#include "mik32_hal_usart.h"

#include "uart_custom_drv.h"
#include "uart_lib.h"
#include "led_drv.h"
//#include "mik32_hal.h"
#ifdef HAS_TIME
#include "time_mcal.h"
#endif
#include "uart_custom_types.h"
#ifdef HAS_STRING_READER
#include "string_reader.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_CLI
#include "cli_config.h"
#include "string_reader.h"
#endif

#include "sys_config.h"

//uint32_t g_uart_rx_cnt = 0;
//static volatile uint8_t rx_buff[UART_COUNT][1];

static const UartInfo_t UartInfo[] = {
#ifdef HAS_UART0
    {
        .num = 0,
        .interrupt_mask = HAL_EPIC_UART_0_MASK,
        .irq_n = INT_NUM_USART_0,
        .UARTx = UART_0,
        .valid = true,
    },
#endif

#ifdef HAS_UART1
    {
        .num = 1,
        .interrupt_mask = HAL_EPIC_UART_1_MASK,
        .irq_n = INT_NUM_USART_1,
        .UARTx = UART_1,
        .valid = true,
    },
#endif
};

static bool UartConfigToMik32UartCfg(const UartConfig_t* const Config, USART_HandleTypeDef* const Mik32Config) {
    bool res = false;
    if(Config) {
        if(Mik32Config) {
            UartInfo_t* Info = UartGetInfo(Config->num);
            if(Info) {
                Mik32Config->Instance = Info->UARTx;
                Mik32Config->frame = UART_FRAME_8BIT;
                Mik32Config->parity_bit = MIK32_CTRL_DISABLE;
                Mik32Config->parity_bit_inversion = MIK32_CTRL_DISABLE;
                Mik32Config->bit_direction = UART_LSB_FIRST;
                Mik32Config->data_inversion = MIK32_CTRL_DISABLE;
                Mik32Config->tx_inversion = MIK32_CTRL_DISABLE;
                Mik32Config->swap = MIK32_CTRL_DISABLE;
                Mik32Config->lbm = MIK32_CTRL_DISABLE;
                Mik32Config->rx_inversion = MIK32_CTRL_DISABLE;
                Mik32Config->transmitting = MIK32_CTRL_ENABLE;
                Mik32Config->receiving = MIK32_CTRL_ENABLE;
                Mik32Config->stop_bit = UART_STOP_BIT_2;
                Mik32Config->mode = USART_MODE_ASYNCHRONOUS;
                Mik32Config->xck_mode = XCK_Mode3;
                Mik32Config->last_byte_clock = MIK32_CTRL_DISABLE;
                Mik32Config->overwrite = MIK32_CTRL_ENABLE;
                Mik32Config->rts_mode = AlwaysEnable_mode;
                Mik32Config->dma_tx_request = MIK32_CTRL_DISABLE;
                Mik32Config->dma_rx_request = MIK32_CTRL_DISABLE;
                Mik32Config->channel_mode = Duplex_Mode;
                Mik32Config->tx_break_mode = MIK32_CTRL_DISABLE;
                Mik32Config->baudrate = Config->baud_rate;

                Mik32Config->Modem.rts = MIK32_CTRL_DISABLE;  // out
                Mik32Config->Modem.cts = MIK32_CTRL_DISABLE;  // in
                Mik32Config->Modem.dtr = MIK32_CTRL_DISABLE;  // out
                Mik32Config->Modem.dcd = MIK32_CTRL_DISABLE;  // in
                Mik32Config->Modem.dsr = MIK32_CTRL_DISABLE;  // in
                Mik32Config->Modem.ri = MIK32_CTRL_DISABLE;   // in
                Mik32Config->Modem.ddis = MIK32_CTRL_DISABLE; // out

                Mik32Config->Interrupt.ctsie = MIK32_CTRL_DISABLE;
                Mik32Config->Interrupt.eie = MIK32_CTRL_DISABLE;
                Mik32Config->Interrupt.idleie = MIK32_CTRL_DISABLE;
                Mik32Config->Interrupt.lbdie = MIK32_CTRL_DISABLE;
                Mik32Config->Interrupt.peie = MIK32_CTRL_DISABLE;
                Mik32Config->Interrupt.rxneie = MIK32_CTRL_DISABLE;
                Mik32Config->Interrupt.tcie = MIK32_CTRL_DISABLE;
                Mik32Config->Interrupt.txeie = MIK32_CTRL_DISABLE;
#if 0
                if(Config->interrupts_on) {
                    Mik32Config->Interrupt.peie = MIK32_CTRL_ENABLE;
                    Mik32Config->Interrupt.txeie = MIK32_CTRL_ENABLE;
                    Mik32Config->Interrupt.tcie = MIK32_CTRL_ENABLE;
                    Mik32Config->Interrupt.rxneie = MIK32_CTRL_ENABLE;
                    Mik32Config->Interrupt.idleie = MIK32_CTRL_ENABLE;
                    Mik32Config->Interrupt.lbdie = MIK32_CTRL_ENABLE;
                    Mik32Config->Interrupt.ctsie = MIK32_CTRL_ENABLE;
                    Mik32Config->Interrupt.eie = MIK32_CTRL_ENABLE;
                }
#endif
                res = true;
            }
        }
    }
    return res;
}

bool uart_send_wait_ll(UartHandle_t* Node, const uint8_t* const data, uint16_t size) {
    bool res = false;
    if(Node) {
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            Node->tx_done = false;
            HAL_USART_WriteByte(&(Node->Handle), (char)data[i]);
            res = uart_wait_tx_done_ll(Node);
            // wait_us(10); //10< < 70 500-ok
            // res = HAL_USART_Transmit(&(Node->Handle), (char) data[i], 0xFFFF);
        }
        res = true;
    }
    return res;
}

UartInfo_t* UartGetInfo(uint8_t num) {
    UartInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(UartInfo);
    for(i = 0; i < cnt; i++) {
        if(num == UartInfo[i].num) {
            if(UartInfo[i].valid) {
                Node = (UartInfo_t*)&UartInfo[i];
                break;
            }
        }
    }
    return Node;
}

#if 0
bool uart_init(void) {
    bool res = true;
    LOG_WARNING(UART, "Init..");
    bool out_res = true;
    uint8_t i = 0;
    uint32_t uart_cnt = uart_get_cnt();
    LOG_INFO(UART, "Cnt: %u", uart_cnt);
    for(i = 0; i <= 10; i++) {
        UartHandle_t* Node = UartGetNode(i);
        const UartConfig_t* Config = UartGetConfig(i);
        if(Node && Config) {
            LOG_DEBUG(UART, "%u SpotConfig", i);
            res = uart_init_one(Node->num);
            if(res) {
                LOG_INFO(UART, "%u Init" LOG_OK, Node->num);
            } else {
                out_res = false;
                LOG_ERROR(UART, "%u InitErr", Node->num);
            }
        }
    }

    return out_res;
}
#endif

#if 0
static bool uart_wait_tx_done_ll(UartHandle_t* Node) {
    bool res = true;
    if(Node) {
        Node->wait_iter = 0;
#ifdef HAS_UART_TX_TIMEOUT
        uint8_t num = get_uart_index(Node->uart_h.Instance);
        uint32_t time_out_us = 0;
        uint32_t baudrate = uart_get_cfg_baudrate(num);
        uint32_t start_us = time_get_us();
        uint32_t dutation_us = 0;
        uint32_t cur_us = 0;
        if(Node->tx_len) {
            time_out_us = calc_transfer_time_us(baudrate, (uint32_t)Node->tx_len + 1);
        } else { // for first call tx_len==0
            time_out_us = calc_transfer_time_us(baudrate, 150);
        }
#endif
        do {
            Node->wait_iter++;
#ifdef HAS_UART_TX_TIMEOUT
            cur_us = time_get_us();
            dutation_us = cur_us - start_us;
            if(500 * time_out_us < dutation_us) {
                Node->tx_time_out_cnt++;
                Node->tx_done = true;
                res = false;
                break;
            }
#endif

            if(Node->tx_done) {
                res = true;
                break;
            }

            if(HAL_UART_STATE_READY == Node->uart_h.gState) {
                res = true; // was true
                break;
            }
        } while(false == Node->tx_done);
    }
    return res;
}
#endif

bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, size_t len) {
    bool res = false;

    return res;
}

bool uart_read(uint8_t num, uint8_t* out_array, uint16_t array_len) {
    bool res = false;

    return res;
}

bool uart_set_baudrate(uint8_t num, uint32_t baudrate) {
    bool res = false;
    return res;
}

uint32_t UartGetBaseClock(uint8_t num) {
    uint32_t clock_hz = 0;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(UartInfo); i++) {
        if(num == UartInfo[i].num) {
            clock_hz = UartInfo[i].clock_hz;
            break;
        }
    }
    return clock_hz;
}

bool uart_get_baud_rate(uint8_t num, uint32_t* const baudrate) {
    bool res = false;
    return res;
}

bool uart_send_ll(uint8_t num, uint8_t* array, uint16_t array_len, bool is_wait) {
    bool res = false;
    // We send mainly from Stack.
    (void)is_wait;
    res = uart_is_allowed(num);
    if(res) {
        if(array && array_len) {
            UartHandle_t* Node = UartGetNode(num);
            if(Node) {
                if(Node->init_done) {
                    Node->tx_buff = NULL;
                } else {
                    res = false;
                }
            } else {
                res = false;
            }
            if(res) {

                /*print from heap*/
#if 0
                    res = uart_wait_send_ll(Node, Node->tx_buff, array_len);
                    if(false == res) {
                        LOG_ERROR(UART, "%u WaitSendErr", num);
                    }
#endif

                /*Print from stack*/
                res = uart_send_wait_ll(Node, array, array_len);
                if(false == res) {
#ifdef HAS_LOG
                    LOG_ERROR(UART, "%u SendWaitErr", num);
#endif
                }
            }

        } else {
#ifdef HAS_LOG
            LOG_ERROR(UART, "DataErr L:%u", array_len);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(UART, "%u NotAllowed", num);
#endif
    }
    return res;
}

#if 0
bool uart_flush(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(Node->init_done) {
            FifoIndex_t cnt = 0;
            do {
                cnt = fifo_get_count(&Node->TxFifo);
                if(cnt) {
                    char TxBuff[50];
                    FifoIndex_t out_len = 0;
                    res = fifo_pull_array(&Node->TxFifo, TxBuff, sizeof(TxBuff), &out_len);
                    if(res) {
                        if(out_len) {
                            res = uart_send_ll(num, (uint8_t*)TxBuff, out_len, true);
                        } else {
                            res = false;
                        }
                    }
                }
            } while(cnt);
        }
    }
    return res;
}
#endif

bool uart_rx_byte_get_ll(UartHandle_t* Node, uint8_t* rx_byte) {
    bool res = false;
    if(rx_byte) {
        Mik32UsartRegRXDATA_t RxDdata;
        RxDdata.dword = Node->UARTx->RXDATA.dword;
        *rx_byte = RxDdata.RDR;
        res = true;
    }
    return res;
}

bool uart_check(void) { return false; }

static bool Mik32UartGetRxByte(UART_TypeDef* const UARTx, uint8_t* const rx_byte) {
    bool res = false;

    static uint8_t old_byte = 0;
#if 0
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    Pad_t PadRts0 = {.port = 0 , .pin = 8,};
    bool gpio_res = gpio_get_state(PadRts0.byte, &logic_level);
    if(gpio_res) {
    	if(GPIO_LVL_HI==logic_level) {
             res = true;
    	}
    }
#endif

    if(UART_RXNE_NEW_DATA == UARTx->FLAGS.RXNE) {
        UARTx->FLAGS.RXNE = UART_RXNE_NEW_DATA;
        res = true;
    }

    uint8_t new_byte = (uint8_t)UARTx->RXDATA.RDR;

    if(UARTx->FLAGS.REACK) {
        // res = true;
    }

    if(old_byte != new_byte) {
        // res = true;
    }

    if(res) {
        *rx_byte = new_byte;
    }
    old_byte = new_byte;

    return res;
}

bool uart_proc_one(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        Node->init_done = true;
        uint8_t rx_byte = 0x00;
        // Just to debug UART Rx PHY
        res = Mik32UartGetRxByte(Node->UARTx, &rx_byte);
        if(res) {
#ifdef HAS_STRING_READER
            Interfaces_t interface_if = UartNumToInterface(num);
            res = string_reader_rx_byte(interface_if, rx_byte);
#endif
        }
#if 0
       char debug_text[200] = {0};
       snprintf(debug_text,sizeof(debug_text),"%s,RXD:0x%x",debug_text, Node->UARTx->RXDATA);
       snprintf(debug_text,sizeof(debug_text),"%s,CTRL1:0x%x",debug_text, Node->UARTx->CONTROL1);
       snprintf(debug_text,sizeof(debug_text),"%s,CTRL2:0x%x",debug_text, Node->UARTx->CONTROL2);
       snprintf(debug_text,sizeof(debug_text),"%s,CTRL3:0x%x",debug_text, Node->UARTx->CONTROL3);
       snprintf(debug_text,sizeof(debug_text),"%s,FLG:0x%x",debug_text, Node->UARTx->FLAGS.dword);
       snprintf(debug_text,sizeof(debug_text),"%s%s",debug_text,CRLF);
       res = true;
       uint8_t data = 0;
       res = uart_rx_byte_get_ll(Node, &data);
       res = gpio_pin_mux_get(PORT_0, 5, &data);
       if(res) {
#if 0
           debug_text[0] = '<';
           debug_text[1] = data;
           debug_text[2] = '>';
           debug_text[3] = '\n';
           debug_text[4] = '\r';
#endif
           res = uart_send_wait_ll(Node, (uint8_t*) debug_text, strlen(debug_text));
       }
#endif

        if(Node->UARTx->FLAGS.TC) {
            Node->UARTx->FLAGS.TC = 1;
        }

        if(Node->UARTx->FLAGS.TXE) {
            Node->UARTx->FLAGS.TXE = 1;
        }

        if(Node->UARTx->FLAGS.CTSIF) {
            Node->UARTx->FLAGS.CTSIF = 1;
        }

        if(Node->UARTx->FLAGS.LBDF) {
            Node->UARTx->FLAGS.LBDF = 1;
        }

        if(Node->UARTx->FLAGS.IDLE) {
            Node->UARTx->FLAGS.IDLE = 1;
        }

        if(Node->UARTx->FLAGS.ORE) {
            Node->UARTx->FLAGS.ORE = 1;
        }

        if(Node->UARTx->FLAGS.NF) {
            Node->UARTx->FLAGS.NF = 1;
        }

        if(Node->UARTx->FLAGS.FE) {
            Node->UARTx->FLAGS.FE = 1;
        }

        if(Node->UARTx->FLAGS.PE) {
            Node->UARTx->FLAGS.PE = 1;
        }
    }
    return res;
}

void HAL_USART_MspInit(USART_HandleTypeDef* setting) {}

bool uart_init_custom(void) {
    bool res = true;
    __HAL_PCC_UART_0_CLK_ENABLE();
    __HAL_PCC_UART_1_CLK_ENABLE();
    __HAL_PCC_EPIC_CLK_ENABLE();
#if 1
    HAL_EPIC_MaskLevelSet(HAL_EPIC_UART_0_MASK);
    HAL_EPIC_MaskLevelSet(HAL_EPIC_UART_1_MASK);
#endif
    // HAL_IRQ_EnableInterrupts();
    return res;
}

bool uart_init_one(uint8_t num) {
    bool res = false;
    const UartConfig_t* Config = UartGetConfig(num);
    if(Config) {// TOGO verify config
        UartHandle_t* Node = UartGetNode(num);
        if(Node) {
            UartInfo_t* Info = UartGetInfo(num);
            if(Info) {
                Node->UARTx = Info->UARTx;
                Node->irq_n = Info->irq_n;
                uint32_t mask = (1U << Info->irq_n);
                PM->CLK_APB_P_SET = mask; // PM_CLOCK_APB_P_UART_1_M
                res = uart_init_general_one(Config, Node);
                if(res) {
                    res = UartConfigToMik32UartCfg(Config, &Node->Handle);
                }
                if(res) {
                    HAL_StatusTypeDef ret = HAL_USART_Init(&(Node->Handle));
                    res = MIK32_HalRetToRes(ret);
                }
                if(res) {
                    /*Enable interrupts on "receiver register not empty" */
                    HAL_USART_TXC_EnableInterrupt(&(Node->Handle));
                    HAL_USART_RXNE_EnableInterrupt(&(Node->Handle));
                    // HAL_USART_PE_EnableInterrupt(&(Node->Handle));
                    // HAL_USART_TXE_EnableInterrupt(&(Node->Handle));
                    // HAL_USART_IDLE_EnableInterrupt(&(Node->Handle));
                    // HAL_USART_RX_Break_EnableInterrupt(&(Node->Handle));
                    // HAL_USART_CTS_EnableInterrupt(&(Node->Handle));
                }
                Node->init_done = true;
                char debug_text[200] = {0};
                debug_text[0] = 'U';
                debug_text[1] = 'A';
                debug_text[2] = 'R';
                debug_text[3] = 'T';
                debug_text[4] = 0x30 + num;
#ifdef HAS_LOG
                snprintf(debug_text, sizeof(debug_text), "%s,HelloFrom UART%u\r\n", debug_text, num);
#else
                res = uart_send_wait_ll(Node, (uint8_t*)debug_text, 6);
#endif
                // led_mono_ctrl(2, true);
            }
        }
    } // config
    return res;
}
