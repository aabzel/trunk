#include "uart_custom_commands.h"

#include <inttypes.h>

#include <zephyr/drivers/uart.h>

#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "ostream.h"
#include "table_utils.h"
#include "uart_bsp.h"
#include "uart_drv.h"
#include "uart_types.h"
#include "writer_config.h"
#include "string_reader.h"


bool uart_custom_diag_commands(int32_t argc, char* argv[]){
    bool res=false;
    const table_col_t cols[] = {
    		{5, "Num"},
    		{6, "baudrate"},
			{6, "parity"},
			{6, "stop_bits"},
            {6, "data_bits"},
			{6, "flow_ctrl"}
    };
    uint8_t uart_num = 0;
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(uart_num = 0; uart_num < UART_COUNT; uart_num++) {
            const struct device *uart_device= UartNum2Dev(uart_num);
            if(uart_device) {
                struct uart_config cfg;
                int ret= uart_config_get(uart_device,&cfg);
                if(0==ret) {
                    cli_printf(TSEP);
                    cli_printf(" %3u  " TSEP, uart_num);
                    cli_printf( " %4u"TSEP, cfg.baudrate);
                    cli_printf( " %4u"TSEP, cfg.parity);
                    cli_printf( " %4u"TSEP, cfg.stop_bits);
                    cli_printf( " %4u"TSEP, cfg.data_bits);
                    cli_printf( " %4u"TSEP, cfg.flow_ctrl);
                    cli_printf(CRLF);
                    res = true;
                }else {
                    LOG_DEBUG(UART, "%u GetCfgErr %d=%s", uart_num, ret,ErrNo2Str(ret));
                    res=false;
                }
            }else{
            	res=false;
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));



    return res;
}
