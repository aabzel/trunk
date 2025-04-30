#include "rs485_diag.h"

#include <stdio.h>
#include <string.h>

#include "rs485_mcal.h"
#include "gpio_diag.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"


const char* Rs485ToStr(const Rs485Config_t* const Config) {
    static char text[40]="";
    if(Config) {
    	strcpy(text,"");
    	snprintf(text,sizeof(text),"%s,N:%u,",text, Config->num);
    	snprintf(text,sizeof(text),"%s,UART:%u,",text, Config->uart_num);
    	snprintf(text,sizeof(text),"%s,Rate:%u Bit/s,",text, Config->bit_rate);
    	snprintf(text,sizeof(text),"%s,%s,",text, GpioPadToStr(Config->DeRe));
    	snprintf(text,sizeof(text),"%s,RxBuff:%u Byte,",text, Config->fifo_heap_size);
    }
    return text;
}

bool rs485_diag(void) {
    bool res = false;
    const table_col_t cols[] = {
    		{5, "Num"},
			{6, "UART"},
			{10, "RxCnt"},
			{10, "TxCnt"},
			{8, "RxBuff"},
    		{6, "IsRx"},
			{6, "init"},
			{10, "RxTime"},
			{10, "Lost"},
    };

    uint32_t num = 0;
    uint32_t cnt = 0;
    cnt = rs485_get_cnt( );
    LOG_INFO(RS485,"CNT:%u", cnt);
    char log_line[150];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(num = 0; num <= cnt; num++) {
        Rs485Handle_t* Node = Rs485GetNode(num);
        if(Node) {
            strcpy(log_line,TSEP);
            snprintf(log_line, sizeof(log_line),"%s %3u " TSEP,log_line, num);
            snprintf(log_line, sizeof(log_line),"%s %4u " TSEP,log_line, Node->uart_num);
            snprintf(log_line, sizeof(log_line),"%s %8u " TSEP,log_line, Node->Flow.byte_rx);
            snprintf(log_line, sizeof(log_line),"%s %8u " TSEP,log_line, Node->Flow.byte_tx);
            snprintf(log_line, sizeof(log_line),"%s %6u " TSEP,log_line, Node->fifo_heap_size);
            snprintf(log_line, sizeof(log_line),"%s %4u " TSEP,log_line, Node->data_in);
            snprintf(log_line, sizeof(log_line),"%s %4u " TSEP,log_line, Node->init);
            snprintf(log_line, sizeof(log_line),"%s %8u " TSEP,log_line, Node->rx_time_stamp_ms);
            snprintf(log_line, sizeof(log_line),"%s %8u " TSEP,log_line, Node->lost_char_count);
            cli_printf("%s" CRLF, log_line);
            cnt++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res ;
}
