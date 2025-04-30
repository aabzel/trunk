#include "uart_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <gpio_types.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "fifo_char.h"
#include "gpio_drv.h"
#include "esp_log.h"
#include "bit_utils.h"
#include "uart_common.h"
#include "driver/uart.h"
#include "log.h"
#ifdef HAS_CLI
#include "uart_string_reader.h"
#endif
#ifdef HAS_NMEA
#include "nmea_protocol.h"
#endif
#ifdef HAS_UBLOX
#include "ubx_protocol.h"
#endif
#include "sys_config.h"

uint32_t g_uart_rx_cnt = 0;

#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM      (CONFIG_EXAMPLE_UART_PORT_NUM)
#define ECHO_UART_BAUD_RATE     (460800)
#define ECHO_TASK_STACK_SIZE    (CONFIG_EXAMPLE_TASK_STACK_SIZE)

#define BUF_SIZE (1024)


UartCfg_t UartCfg[2]={
                      {.tx_io_num=DIO_UART_CLI_TX,
                       .rx_io_num=DIO_UART_CLI_RX},
                      {.tx_io_num=DIO_GNSS_TXD,
                       .rx_io_num=DIO_GNSS_RXD}
};

//static intr_handle_t handle_console;

uart_config_t UartConfig[2] = {{
    .baud_rate = ECHO_UART_BAUD_RATE,
    .data_bits = UART_DATA_8_BITS,
    .parity    = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_APB,
},

{
    .baud_rate = 9600,
    .data_bits = UART_DATA_8_BITS,
    .parity    = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_APB,
}
};

bool usart_set_baudrate(uint8_t uart_num, uint16_t baudrate){
    bool res = false;
    return res;
}

static void uart0_rx_thread(void *arg){
	uint8_t data[128];
	size_t length = 0;
    while (1) {
    	length = 0;
    	uart_get_buffered_data_len(UART_NUM_CLI, (size_t*)&length);
    	if(0<length){
#ifdef HAS_UART_RX_DEBUG
          	gpio_toggle(GPIO_NUM_4);
#endif
        	length =(size_t) uart_read_bytes(UART_NUM_CLI, data, length, 100);
          	int i=0;
        	for(i=0;i<length;i++){
        	    huart[0].rx_cnt++;
            	huart[UART_NUM_CLI].tx_int = true;
            	huart[UART_NUM_CLI].rx_int = true;
#ifdef HAS_CLI
                uart_string_reader_rx_callback(&cmd_reader, data[i]);
#endif /*HAS_CLI*/
    	    }
    	}
    	vTaskDelay(10 / portTICK_RATE_MS);
	}
}


static void uart1_rx_thread(void *arg){
    uint8_t data[128];
    size_t length = 0;
    bool res = false;
    while (1) {
        length = 0;
        uart_get_buffered_data_len(UART_NUM_GNSS, (size_t*)&length);
        if(0<length){
#ifdef HAS_UART_RX_DEBUG
            gpio_toggle(GPIO_NUM_4);
#endif
            length =(size_t) uart_read_bytes(UART_NUM_GNSS, data, length, 100);
            int i=0;
            for(i=0;i<length;i++){
               huart[1].rx_cnt++;
#ifdef HAS_UART1_FWD
               if(true == huart[1].is_uart_fwd[0]) {
                  res = fifo_push(&huart[0].TxFifo, data[i]);
                  if(false == res) {
                      huart[0].error_cnt++;
                  }
        }
#endif /*HAS_UART1_FWD*/
#ifdef HAS_NMEA
                res = nmea_proc_byte(data[i]); //Exeption here
                if(false==res){
                    //LOG_ERROR(NMEA,"ProcByteErr 0x%x",data[i]);
                }
#endif /*HAS_NMEA*/

#ifdef HAS_UBLOX
                res = ubx_proc_byte(data[i]);
                if(false==res){
                   // LOG_ERROR(UBX,"ProcByteErr 0x%x",data[i]);
                }
#endif /*HAS_UBLOX*/
                huart[UART_NUM_GNSS].tx_int = true;
                huart[UART_NUM_GNSS].rx_int = true;
            }
        }
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}


static bool init_uart_one(uint8_t uart_num, char* name) {
    bool res = true;
    strncpy(huart[uart_num].name, name, sizeof(huart[uart_num].name));
    int intr_alloc_flags = 0;
    esp_err_t ret;
    ret=uart_driver_install(uart_num, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags);
    if(ESP_OK==ret){

    }
    ret=uart_param_config(uart_num, &UartConfig[uart_num]);
    if(ESP_OK==ret){

    }
    ret=uart_set_pin(uart_num, UartCfg[uart_num].tx_io_num, UartCfg[uart_num].rx_io_num, ECHO_TEST_RTS, ECHO_TEST_CTS);
    if(ESP_OK==ret){

    }

    // register new UART subroutine
    //uart_isr_register(UART_NUM_CLI, uart_intr_handle, NULL, ESP_INTR_FLAG_LEVEL1, NULL);
    // enable RX interrupt
    ret=uart_enable_rx_intr(uart_num);
    if(ESP_OK==ret){

    }
    char str[20] = "0";
    snprintf(str, sizeof(str), "UART%u_task", uart_num);
    uart_write_bytes(uart_num, (const char *) str, strlen(str));
    switch(uart_num){
    case 0:
        xTaskCreate(uart0_rx_thread, str, 5000, NULL, 10, NULL);
        break;
    case 1:
        xTaskCreate(uart1_rx_thread, str, 5000, NULL, 10, NULL);
        break;
    default : break;
    }
    return res;
}
// Receive buffer to collect incoming data
uint8_t rxbuf[256];
/*
 * Define UART interrupt subroutine to ackowledge interrupt
 */
#if 0
static void IRAM_ATTR uart_intr_handle(void *arg){
	uint8_t data[128];
	size_t length = 0;
	uart_get_buffered_data_len(UART_NUM_CLI, (size_t*)&length);
	if(0<length){
    	length =(size_t) uart_read_bytes(UART_NUM_CLI, data, length, 100);
    	int i = 0;
    	for (i=0; i<length; i++) {
        	gpio_toggle(GPIO_NUM_4);
        	huart[UART_NUM_CLI].tx_int = true;
        	huart[UART_NUM_CLI].rx_int = true;
#ifdef HAS_CLI
            uart_string_reader_rx_callback(&cmd_reader, data[i]);
#endif /*HAS_CLI*/

    	}
	}
}
#endif


bool uart_init(void) {
    bool res = true;
    res = init_uart_one(UART_NUM_CLI,"CLI");
    res = init_uart_one(UART_NUM_GNSS,"GNSS");
    return res;
}

static bool uart_send_ll(uint8_t uart_num, uint8_t* tx_buffer, uint16_t len) {
    bool res = false;
    uart_write_bytes(uart_num, (const char *) tx_buffer, len);
    return res;
}

bool uart_send(uint8_t uart_num, uint8_t* array, uint16_t array_len, bool is_wait) {
    bool res = false;
    (void)is_wait;
    if(array && (uart_num < UART_COUNT) && (0 < array_len)) {
        res = uart_send_ll(uart_num, array, array_len);
    }
    return res;
}

bool uart_read(uint8_t uart_num, uint8_t* out_array, uint16_t array_len) {
    bool res = false;
    uart_read_bytes(UART_NUM_CLI, out_array, array_len, 100);
    return res;
}

bool proc_uarts(void) { return true; }

uint32_t uart_get_baud_rate(uint8_t uart_num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling) {
    bool res = true;
    return res;
}
