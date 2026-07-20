#include "dma_custom_diag.h"

#include <stdio.h>

#include "bit_diag.h"
#include "dma_const.h"
#include "dma_custom_const.h"
#include "str_utils.h"
#include "dma_diag.h"
#include "microcontroller.h"
#include "num_to_str.h"
#include "debugger.h"
#include "dma_channel_custom.h"
#include "table_utils.h"
#include "mcal_types.h"

const Reg32_t DmaStreamReg[] = {
    { .offset = 0x00, .name = "DMA_SxCR",   .num = 1, .size = 4, .valid = true,  .access = ACCESS_READ_WRITE,    },
    { .offset = 0x04, .name = "DMA_SxNDTR", .num = 2, .size = 4, .valid = true,  .access = ACCESS_READ_WRITE,    },
    { .offset = 0x08, .name = "DMA_SxPAR",  .num = 3, .size = 4, .valid = true,  .access = ACCESS_READ_WRITE,    },
    { .offset = 0x0C, .name = "DMA_SxM0AR", .num = 4, .size = 4, .valid = true,  .access = ACCESS_READ_WRITE,    },
    { .offset = 0x10, .name = "DMA_SxM1AR", .num = 5, .size = 4, .valid = true,  .access = ACCESS_READ_WRITE,    },
    { .offset = 0x14, .name = "DMA_SxFCR",  .num = 6, .size = 4, .valid = true,  .access = ACCESS_READ_WRITE,    },
};

uint32_t dma_stream_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(DmaStreamReg);
    return cnt;
}

uint8_t DmaStmDataSizeToBits(const DmaStm32Aligmant_t code) {
    uint8_t bit_num = 0;
    switch(code) {
    case DMA_STM32_ALIGNMENT_BYTE:        bit_num = 8;        break;
    case DMA_STM32_ALIGNMENT_HALF_WORD:   bit_num = 16;        break;
    case DMA_STM32_ALIGNMENT_WORD:        bit_num = 32;        break;
    default:        break;
    }
    return bit_num;
}


const char* DmaStmDirToStr(const DmaStmDataTransferDirection_t dir) {
    const char*  name = "?";
    switch(dir) {
        case DMA_STM32_DIR_PERIPHERAL_TO_MEMORY:        name = "Per->mem";        break;
        case DMA_STM32_DIR_MEMORY_TO_PERIPHERAL:   name = "Mem->per";        break;
        case DMA_STM32_DIR_MEMORY_TO_MEMORY:        name = "Mem->mem";        break;
        default:        break;
    }
    return name;
}

const char* DmaStmIncrToStr(const DmaStmIncrementMode_t increment_mode){
    const char*  name = "?";
    switch(increment_mode) {
        case DMA_STM32_INCR_MODE_OFF:  name = "off";        break;
        case DMA_STM32_INCR_MODE_ON:   name = "on";        break;
        default:        break;
    }
    return name;
}

const char* DmaStmMoveModeToStr(const DmaStmMoveMode_t move_mode) {
    const char*  name = "?";
    switch(move_mode) {
        case DMA_STM32_MOVE_MODE_CIRCULAR:  name = "Circul";  break;
        case DMA_STM32_MOVE_MODE_NORMAL:    name = "Normal";  break;
        default:        break;
    }
    return name;
}

const char* DmaStmPriorityLevelToStr(const DmaStmPriorityLevel_t priority_level) {
    const char*  name = "?";
    switch(priority_level) {
        case DMA_STM32_PRIORITY_LEVEL_LOW:        name = "Low";        break;
        case DMA_STM32_PRIORITY_LEVEL_MEDIUM:     name = "Med";        break;
        case DMA_STM32_PRIORITY_LEVEL_HIGH:       name = "Hi";        break;
        case DMA_STM32_PRIORITY_LEVEL_VERY_HIGH:  name = "VerHi";        break;
        default:        break;
    }
    return name;
}

const char* dma_channel_to_str(uint8_t dma_num, uint8_t stream_num, uint32_t channel) {
    static char temp[120];
    memset(temp, 0, sizeof(temp));
    strcpy(temp, "");
    snprintf(temp, sizeof(temp), "DMA%u_", dma_num);
    snprintf(temp, sizeof(temp), "%sStream_%u_", temp, stream_num);
    snprintf(temp, sizeof(temp), "%sCh_%u", temp, channel);
    return temp;

}

bool dma_channel_diag_custom(void){
    bool res = false;
    static const table_col_t cols[] = {
            {21, "DMAx_Stream_y_Ch_z"},
            {5, "En"},
            {3, "TxInt"},
            {3, "HalfTxInt"},
            {10, "Dir"},
            {5, "mDat"},
            {5, "pDat"},
            {5, "mInc"},
            {5, "pInc"},
            {8, "mode"},
            {8, "Prio"},
            {41, "bin"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t dma_num = 0;
    for (dma_num=1; dma_num<=DMA_COUNT; dma_num++) {
        uint8_t stream_num = 0;
        for(stream_num=0; stream_num<DMA_STREAM_COUNT; stream_num++){
            DMA_Stream_TypeDef* DMA_STREAMx = dma_stream_num_2_prt(  dma_num,   stream_num);
            if(DMA_STREAMx){
                DmaStreamConfReg_t CfgReg;
                CfgReg.dword = DMA_STREAMx->CR;
                char temp_str[220] = {0};
                strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s %17s  " TSEP, temp_str, dma_channel_to_str(  dma_num,   stream_num,   CfgReg.chsel) );
                snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOffToStr(CfgReg.en));
                snprintf(temp_str, sizeof(temp_str), "%s %1u " TSEP, temp_str, CfgReg.tcie);
                snprintf(temp_str, sizeof(temp_str), "%s %1u " TSEP, temp_str, CfgReg.htie);
                snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, DmaStmDirToStr(CfgReg.dir));
                snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str,  DmaStmDataSizeToBits(CfgReg.msize));
                snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str,  DmaStmDataSizeToBits(CfgReg.psize));
                snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str,  DmaStmIncrToStr(CfgReg.minc));
                snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str,  DmaStmIncrToStr(CfgReg.pinc));
                snprintf(temp_str, sizeof(temp_str), "%s %6s " TSEP, temp_str, DmaStmMoveModeToStr(CfgReg.circ));
                snprintf(temp_str, sizeof(temp_str), "%s %5s  " TSEP, temp_str, DmaStmPriorityLevelToStr(CfgReg.pl));
                snprintf(temp_str, sizeof(temp_str), "%s %32s  " TSEP, temp_str, utoa_bin32(CfgReg.dword));
                cli_printf("%s" CRLF, temp_str);
                res = true;
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool dma_channel_diag_low_level(char* key_word1, char* key_word2){
    uint8_t dma_num = 0;
    bool res = false;
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
           char temp_str[120]={0};
           strcpy(temp_str, TSEP);
               snprintf(temp_str, sizeof(temp_str), "%s %1u  " TSEP, temp_str, dma_num);
               snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, stream_num);
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,BitToStr(Reg.tcif,"1","0") );
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,BitToStr(Reg.htif,"1","0"));
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,BitToStr(Reg.teif,"1","0"));
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,BitToStr(Reg.dmeif,"1","0"));
               snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,BitToStr(Reg.feif,"1","0"));
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

bool  dma_channel_reg_map(const DmaInfoChannel_t DmaPad) {
    bool res = false ;
    DMA_Stream_TypeDef* STREAMx= DmaChannelToDMAx(DmaPad.dma_num, DmaPad.stream);
    if(STREAMx){
        LOG_WARNING(DMA_CHANNEL,"%s, Regs",DmaInfoPadToStr(&DmaPad));
        uint32_t reg_cnt= dma_stream_reg_cnt();
        res = debug_raw_reg_diag(DMA_CHANNEL , (uint32_t) STREAMx,DmaStreamReg, reg_cnt );
    }
    return res;
}
