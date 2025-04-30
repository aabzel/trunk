#include "dma_commands.h"

#include <stdio.h>

#include "convert.h"
#include "str_utils.h"
#include "common_diag.h"
#include "data_utils.h"
#include "dma_drv.h"
#include "dma_mcal.h"
#include "dma_diag.h"
#include "dma_config.h"
#include "dma_types.h"
#include "log.h"
#include "at32f435_437.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

static bool dma_diag_low_level_diag(char* key_word1, char* key_word2){
    uint8_t dma_num = 0;
    bool res = false;
    char temp_str[120];
    uint16_t num = 0;
    static const table_col_t cols[] = {
    		{5, "num"},
    		{4, "dma"},
    		{5, "strm"},
			{3, "tcif"},
			{3, "htif"},
			{3, "teif"},
			{3, "dmeif"},
			{3, "feif"}
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for (dma_num=1; dma_num<=DMA_COUNT; dma_num++) {
       uint8_t stream_num = 0;
       for(stream_num=0; stream_num<DMA_STREAM_COUNT; stream_num++){
           DmaStreamIntStatusReg_t Reg = DmaGetStream(dma_num, stream_num);
           strcpy(temp_str, TSEP);
               snprintf(temp_str, sizeof(temp_str), "%s %1u  " TSEP, temp_str, dma_num);
               snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, stream_num);
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,Bit2Str(Reg.tcif) );
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,Bit2Str(Reg.htif));
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,Bit2Str(Reg.teif));
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,Bit2Str(Reg.dmeif));
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,Bit2Str(Reg.feif));
               if(is_contain(temp_str, key_word1, key_word2)) {
                   cli_printf(TSEP " %3u ", num);
                   cli_printf("%s" CRLF, temp_str);
                   num++;
               }
       }
       table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool dma_diag_stream_command(int32_t argc, char* argv[]){
    bool res = false;
    static const table_col_t cols[] = {
    		{4, "Dma"},
    		{5, "Strm"},
			{3, "En"},
			{3, "TxInt"},
			{3, "HalfTxInt"},
			{5, "Dir"},
			{5, "Chn"},
			{5, "mDat"},
			{5, "pDat"},
	        {5, "mInc"},
	        {5, "pInc"},
	        {6, "mode"},
    };
    char temp_str[120];
    uint8_t dma_num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for (dma_num=1; dma_num<=DMA_COUNT; dma_num++) {
        uint8_t stream_num = 0;
        for(stream_num=0; stream_num<DMA_STREAM_COUNT; stream_num++){
        	DMA_Stream_TypeDef* StreamBase=gma_stream_num_2_prt(  dma_num,   stream_num);
        	if(StreamBase){
        		DmaStreamConfReg_t Reg;
        		Reg.reg_val=StreamBase->CR;
        		strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s %1u  " TSEP, temp_str, dma_num);
                snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, stream_num);
                snprintf(temp_str, sizeof(temp_str), "%s %1u " TSEP, temp_str, Reg.en);
                snprintf(temp_str, sizeof(temp_str), "%s %1u " TSEP, temp_str, Reg.tcie);
                snprintf(temp_str, sizeof(temp_str), "%s %1u " TSEP, temp_str, Reg.htie);
                snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, DmaDir2Str(Reg.dir));
                snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str, Reg.chsel);
                snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str,  DmaDataSizeBits2Str(Reg.msize));
                snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str,  DmaDataSizeBits2Str(Reg.psize));
                snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str,  DmaIncr2Str(Reg.minc));
                snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str,  DmaIncr2Str(Reg.pinc));
                snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, DmaMode2Str(Reg.circ));
                cli_printf("%s" CRLF, temp_str);
        	}
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool dma_diag_low_level_command(int32_t argc, char* argv[]){
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(GPIO, "Usage: ddl keyWord");
    }
    if(true == res) {
        res = dma_diag_low_level_diag(keyWord1, keyWord2);
    }
    return res;
}

bool dma_diag_command(int32_t argc, char* argv[]) {
    uint8_t i=0;
    bool res = false;
    static const table_col_t cols[] = {
    {5, "No"},
    {5, "rem"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = dma_get_cnt();
    for(i=0; i<=cnt; i++){
        DmaHandle_t* DmaNode = DmaGetNode(i);
        if(DmaNode){
            uint32_t remaining =__HAL_DMA_GET_COUNTER(&DmaNode->dma_h);
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, DmaNode->num);
            cli_printf(" %u " TSEP, remaining);
            cli_printf(CRLF);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool dma_stop_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t dma_num = 2;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dma_num);
        if(false == res) {
            LOG_ERROR(DMA, "ParseErr DmaNum [1..2]");
        }
    }
    if(res){
        res= dma_stop(dma_num);
        if(res){
            LOG_INFO(DMA, LOG_OK);
        }else{
            LOG_INFO(DMA, LOG_ER);
        }
    }else{
        LOG_ERROR(DMA, "Usage: ds DmaNum");
    }
    return res;
}

bool dma_init_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0==argc){
        res= dma_init();
        if(res){
            LOG_INFO(DMA,"Init" LOG_OK);
        }else{
            LOG_INFO(DMA,"Init" LOG_ER);
        }
    }
    uint8_t dma_num = 2;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dma_num);
        if(false == res) {
            LOG_ERROR(DMA, "ParseErr DmaNum [1..2]");
        }
    }
    if(res && 0<argc){
        res= dma_init_ll(dma_num);
        if(res){
            LOG_INFO(DMA, LOG_OK);
        }else{
            LOG_INFO(DMA, LOG_ER);
        }
    }else{
        LOG_ERROR(DMA, "Usage: di DmaNum");
    }
    return res;
}
