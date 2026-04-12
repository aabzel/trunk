#include "dac_custom_diag.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "dac_custom_const.h"
#include "dac_mcal.h"
#include "artery_at32f4xx.h"
#include "table_utils.h"
#include "writer_config.h"
#include "num_to_str.h"
#include "debugger.h"
#include "dac_custom_drv.h"

char* DacMode2Str(uint8_t code) {
    char *name = "?";
    switch (code) {
    case DAC_MODE_DAC:
        name = "DAC";
        break;
    case DAC_MODE_SMBUS:
        name = "SMBus";
        break;
    }
    return name;
}

char* DacBusRole2Str(uint8_t code) {
    char *name = "?";
    switch (code) {
    case DAC_BUS_ROLE_SLAVE:
        name = "Slave";
        break;
    case DAC_BUS_ROLE_MASTER:
        name = "Master";
        break;
    }
    return name;
}

char* DacBusState2Str(uint8_t code) {
    char *name = "?";
    switch (code) {
    case DAC_BUS_STATE_SPARE:
        name = "Spare";
        break;
    case DAC_BUS_STATE_BUSY:
        name = "Busy";
        break;
    }
    return name;
}

char* DacDir2Str(uint8_t code) {
    char *name = "?";
    switch (code) {
    case DAC_DIR_RX:
        name = "Rx";
        break;
    case DAC_DIR_TX:
        name = "Tx";
        break;
    }
    return name;
}

const char* DacErrToStr(dac_status_type ret) {
    char *name = "?";
    switch ((uint8_t) ret) {
    case DAC_OK:
        name = "Ok";
        break;
    case DAC_ERR_STEP_1:
        name = "Step1_BUSY";
        break;
    case DAC_ERR_STEP_2:
        name = "Step2TDIS";
        break;
    case DAC_ERR_STEP_3:
        name = "Step3";
        break;
    case DAC_ERR_STEP_4:
        name = "Step4_TDC";//transmit data complete flag
        break;
    case DAC_ERR_STEP_5:
        name = "Step5";
        break;
    case DAC_ERR_STEP_6:
        name = "Step6";
        break;
    case DAC_ERR_STEP_7:
        name = "Step7";
        break;
    case DAC_ERR_STEP_8:
        name = "Step8";
        break;
    case DAC_ERR_STEP_9:
        name = "Step9";
        break;
    case DAC_ERR_STEP_10:
        name = "Step10";
        break;
    case DAC_ERR_STEP_11:
        name = "Step11";
        break;
    case DAC_ERR_STEP_12:
        name = "Step12";
        break;
    case DAC_ERR_TIMEOUT:
        name = "TIMEOUT";
        break;
    case DAC_ERR_TCRLD:
        name = "TCRLD";
        break;
    case DAC_ERR_TDC:
        name = "TDC";
        break;
    case DAC_ERR_ACKFAIL:
        name = "ACKFAIL";
        break;
    case DAC_ERR_STOP:
        name = "STOP";
        break;
    case DAC_ERR_ADDR:
        name = "ADDR";
        break;
    case DAC_ERR_INTERRUPT:
        name = "INTERRUPT";
        break;
    }
    return name;
}


static const char * TxDirToStr(dac_transfer_dir_type code){
    const char *  name="?";
    switch(code){
    case DAC_DIR_TRANSMIT:name="Tx"; break;
    case DAC_DIR_RECEIVE:name="Rx"; break;
    default : break;
    }
    return name;
}



bool dac_diag_custom(void) {
    bool res = false;
    static const table_col_t cols[] = { { 5, "No" }, { 5, "DAC" },
            { 8, "TxAddr" }, { 5, "Dir" }, { 7, "Match" }, { 7, "Pec" },

    };
    uint16_t num = 1;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    char temp_str[120];
    for (i = 0; i <= DAC_COUNT; i++) {
        DacHandle_t *Node = DacGetNode(i);
        if (Node) {
            uint16_t transfer_addr = dac_transfer_addr_get(Node->DACx);
            dac_transfer_dir_type tx_dir = dac_transfer_dir_get(Node->DACx);
            uint8_t matched_addr = dac_matched_addr_get(Node->DACx);
            uint8_t pec_value = dac_pec_value_get(Node->DACx);

            res = true;
            strcpy(temp_str, TSEP);

#if 0
                flag_status dac_interrupt_get(Node->DACx, uint16_t source);
                flag_status dac_flag_get(Node->DACx, uint32_t flag);
                flag_status dac_interrupt_flag_get(Node->DACx, uint32_t flag);
#endif

            snprintf(temp_str, sizeof(temp_str), "%s  0x%04x " TSEP, temp_str, transfer_addr);
            snprintf(temp_str, sizeof(temp_str), "%s  %3s " TSEP, temp_str, TxDirToStr(tx_dir));
            snprintf(temp_str, sizeof(temp_str), "%s  0x%02x " TSEP, temp_str, matched_addr);
            snprintf(temp_str, sizeof(temp_str), "%s  0x%02x " TSEP, temp_str, pec_value);

            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);

            num++;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool dac_raw_reg_diag(uint8_t num){
    bool res = false;
    char temp_str[120]={0};
    const DacInfo_t* Info=DacGetInfo(num);
    if(Info) {
    	uint32_t reg_cnt = dac_reg_cnt();
        cli_printf("cnt:%u" CRLF, reg_cnt);

    	uint32_t r = 0 ;
        static const table_col_t cols[] = {
        		{ 13, "Name" },
				{ 6, "offset" },
				{ 12, "Addr" },
				{ 12, "ValHex" },
                { 43, "ValBin" },

        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(r=0;r<reg_cnt;r++){
            strcpy(temp_str, TSEP);
        	uint32_t addr_val = ((uint32_t)Info->DACx)+DacReg[r].offset;
        	uint32_t value=read_addr_32bit( addr_val);
        	snprintf(temp_str, sizeof(temp_str), "%s %11s " TSEP, temp_str, DacReg[r].name);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%02x " TSEP, temp_str, DacReg[r].offset);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, addr_val);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, value);
            snprintf(temp_str, sizeof(temp_str), "%s 0b%s " TSEP, temp_str, utoa_bin32(value));

            cli_printf("%s" CRLF, temp_str);
            res = true;
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}
