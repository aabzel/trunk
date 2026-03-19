#include "i2c_fsm_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "i2c_fsm.h"
#include "i2c_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

bool i2c_fsm_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},     {5, "SlaveAddr"}, {7, "Operat"}, {7, "State"},  {7, "Input"},
        {7, "RxSize"}, {7, "TxSize"},    {7, "TxData"}, {7, "RxData"},
    };
    uint16_t num = 1;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    char temp_str[120];
    for(i = 0; i <= I2C_COUNT; i++) {
        I2cHandle_t* Node = I2cGetNode(i);
        if(Node) {
            const I2cConfig_t* Config = I2cGetConfig(i);
            if(Config) {
                res = true;
                strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s  %1u  " TSEP, temp_str, (unsigned int)i);
                snprintf(temp_str, sizeof(temp_str), "%s %0x02 " TSEP, temp_str, (unsigned int)Node->slave_addr);
                snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, (unsigned int)Node->fsm_operation);
                snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, (unsigned int)Node->fsm_state);
                snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, (unsigned int)Node->fsm_input);
                snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, (unsigned int)Node->fsm_input_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->RxDataSize);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->TxDataSize);

                snprintf(temp_str, sizeof(temp_str), "%s %p " TSEP, temp_str, (unsigned int)Node->TxData);
                snprintf(temp_str, sizeof(temp_str), "%s %p " TSEP, temp_str, (unsigned int)Node->RxData);
                cli_printf("%s" CRLF, temp_str);
            }
            num++;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2c_fsm_scan_base_diag(uint8_t num) {
    bool res = false;
    LOG_INFO(I2C_FSM, "InterfaceNum %u", num);
    static const table_col_t cols[] = {
        {4, "--"}, {4, "x0"}, {4, "x1"}, {4, "x2"}, {4, "x3"}, {4, "x4"}, {4, "x5"}, {4, "x6"}, {4, "x7"},
        {4, "x8"}, {4, "x9"}, {4, "xA"}, {4, "xB"}, {4, "xC"}, {4, "xD"}, {4, "xE"}, {4, "xF"},
    };
    Type8Union_t un8;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t l = 0, h = 0;
    uint32_t spot_cnt = 0;
    bool lres = false;
    for(h = 0; h <= 0xF; h++) {
        un8.nibble_h = h;
        cli_printf(TSEP);
        cli_printf(" %xx " TSEP, h);
        for(l = 0; l <= 0xF; l++) {
            un8.nibble_h = h;
            un8.nibble_l = l;
            lres = i2c_is_valid_address(un8.u8);
            if(lres) {
                lres = i2c_fsm_check_addr(num, un8.u8);
                if(lres) {
                    spot_cnt++;
                    cli_printf(" %02x " TSEP, un8.u8);
                    res = true;
                } else {
                    cli_printf(" -- " TSEP);
                }
#ifdef HAS_TIME
                wait_in_loop_ms(30); // 20ms <???< ????
#endif
            } else {
                cli_printf(" .. " TSEP);
            }
        }
        cli_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    cli_printf("SpotASICs:%u" CRLF, spot_cnt);
    return res;
}

bool i2c_fsm_diag_one(uint8_t num) {
    bool res = false;
    return res;
}

const char* I2cFsmOperationToStr(I2cFsmOperation_t operation) {
    char* name = "?";
    switch(operation) {
    case I2C_FSM_OPERATION_EMPTY:
        name = "EMPTY";
        break;
    case I2C_FSM_OPERATION_CHECK_ADDR:
        name = "CHECK_ADDR";
        break;
    case I2C_FSM_OPERATION_WRITE:
        name = "WRITE";
        break;
    case I2C_FSM_OPERATION_RAED:
        name = "RAED";
        break;
    case I2C_FSM_OPERATION_WRITE_MEM:
        name = "WRITE_MEM";
        break;
    case I2C_FSM_OPERATION_READ_MEM:
        name = "READ_MEM";
        break;
    case I2C_FSM_OPERATION_NOP:
        name = "NOP";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* I2cFsmStateToStr(I2cFsmState_t fsm_state) {
    char* name = "?";
    switch(fsm_state) {
    case I2C_FSM_STATE_IDLE:
        name = "IDLE";
        break;
    case I2C_FSM_STATE_WAIT_START1:
        name = "WAIT_START1";
        break;
    case I2C_FSM_STATE_WAIT_BUSY:
        name = "WAIT_BUSY";
        break;
    case I2C_FSM_STATE_WAIT_TX_DATA:
        name = "WAIT_TX_DATA";
        break;
    case I2C_FSM_STATE_WAIT_START2:
        name = "WAIT_START2";
        break;
    case I2C_FSM_STATE_WAIT_TX_CHIP_READ_ADDR:
        name = "WAIT_TX_CHIP_READ_ADDR";
        break;
    case I2C_FSM_STATE_WAIT_READ_DATA:
        name = "WAIT_READ_DATA";
        break;
    case I2C_FSM_STATE_WAIT_TX_7BIT_ADDR:
        name = "TX_7BIT_ADDR";
        break;
    case I2C_FSM_STATE_WAIT_TX_STOP:
        name = "TX_STOP";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* I2cFsmInputToStr(I2cFsmInput_t fsm_input) {
    char* name = "?";
    switch(fsm_input) {
    case I2C_FSM_INPUT_TX_DIR:
        name = "TX_DIR";
        break;
    case I2C_FSM_INPUT_RX_ACK:
        name = "RX_ACK";
        break;
    case I2C_FSM_INPUT_TX_MODE:
        name = "TRMODE";
        break;
    case I2C_FSM_INPUT_START_DONE:
        name = "StartDone";
        break;
    case I2C_FSM_INPUT_STOP_SIGNAL_DONE:
        name = "StopDone";
        break;
    case I2C_FSM_INPUT_TX_DATA_DONE:
        name = "TX_DATA_DONE";
        break;
    case I2C_FSM_INPUT_RX_DATA_FULL:
        name = "RX_DATA_FULL ";
        break;
    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY:
        name = "TX_DATA_BUFF_EMPTY";
        break;
    case I2C_FSM_INPUT_BUS_ERROR:
        name = "BusErr";
        break;
    case I2C_FSM_INPUT_GENERATE_START:
        name = "GenStart";
        break;
    case I2C_FSM_INPUT_NONE:
        name = "None";
        break;
    case I2C_FSM_INPUT_ADDRH_9_8_ACK:
        name = "Addr98ack";
        break;
    case I2C_FSM_INPUT_ARBITRATION_LOST:
        name = "ArbitLost";
        break;
    case I2C_FSM_INPUT_ACKNOWLEDGE_FAIL:
        name = "AckFail";
        break;
    case I2C_FSM_INPUT_OVERFLOW_OR_UNDERFLOW:
        name = "OverUderFlow";
        break;
    case I2C_FSM_INPUT_RX_PEC:
        name = "RxPec";
        break;
    case I2C_FSM_INPUT_BUS_BUSY:
        name = "BusBusy";
        break;
    case I2C_FSM_INPUT_GENERAL_CALL_ADDRESS_RECEIVED:
        name = "AddrRx";
        break;
    case I2C_FSM_INPUT_SMBUS_TIMEOUT:
        name = "?";
        break;
    case I2C_FSM_INPUT_SMBUS_ALERT:
        name = "?";
        break;
    case I2C_FSM_INPUT_SMBUS_DEVICE_ADDRESS_RX:
        name = "?";
        break;
    case I2C_FSM_INPUT_SMBUS_HOST_ADDRESS_RX:
        name = "?";
        break;
    case I2C_FSM_INPUT_OWN_ADDRESS_2_RX:
        name = "Idle";
        break;

    case I2C_FSM_INPUT_CHIP_ADDR_ACK_TIMEOUT:
        name = "CHIP_ADDR_ACK_TIMEOUT";
        break;
    case I2C_FSM_INPUT_READ_DATA_TIMEOUT:
        name = "READ_DATA_TIMEOUT";
        break;
    case I2C_FSM_INPUT_RX_ACK_TIMEOUT:
        name = "RX_ACK_TIMEOUT";
        break;
    case I2C_FSM_INPUT_START_SIGNAL_TIMEOUT:
        name = "START_SIGNAL_TIMEOUT";
        break;
    case I2C_FSM_INPUT_TIME_OUT:
        name = "TIME_OUT";
        break;
    case I2C_FSM_INPUT_STOP_SIGNAL_TIMEOUT:
        name = "STOP_SIGNAL_TIMEOUT";
        break;
    case I2C_FSM_INPUT_SLAVE_SENDS_DATA:
        name = "SLAVE_SENDS_DATA";
        break;
    case I2C_FSM_INPUT_PEC_RX_ERROR:
        name = "PEC_RX_ERROR";
        break;
    case I2C_FSM_INPUT_ADDR_HEAD_MATCH:
        name = "ADDR_HEAD_MATCH";
        break;
    case I2C_FSM_INPUT_TX_DONE_WAIT_LOAD:
        name = "TX_DONE_WAIT_LOAD";
        break;
    case I2C_FSM_INPUT_TX_DATA_INTERR_STATUS:
        name = "TX_DATA_INTERR_STATUS";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* I2cFsmNodeToStr(I2cHandle_t* const Node) {
    static char text[150] = "";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin_cnt);                          //
        snprintf(text, sizeof(text), "%sOp:%s,", text, I2cFsmOperationToStr(Node->fsm_operation)); //
        snprintf(text, sizeof(text), "%sSlvAdd:0x%x,", text, Node->slave_addr);                    //
        snprintf(text, sizeof(text), "%sState:" VT_SETCOLOR_YELLOW "%s," VT_SETCOLOR_BLUE, text,
                 I2cFsmStateToStr(Node->fsm_state)); //
        snprintf(text, sizeof(text), "%sIn:" VT_SETCOLOR_PINK "%s" VT_SETCOLOR_BLUE ",", text,
                 I2cFsmInputToStr(Node->fsm_input));                        //
        snprintf(text, sizeof(text), "%sTxDat:%p,", text, Node->TxData);    //
        snprintf(text, sizeof(text), "%sRxDat:%p,", text, Node->RxData);    //
        snprintf(text, sizeof(text), "%sRxSz:%u,", text, Node->RxDataSize); //
        snprintf(text, sizeof(text), "%sTxSz:%u,", text, Node->TxDataSize); //
        snprintf(text, sizeof(text), "%sInCnt:%u,", text, Node->fsm_input_cnt);
    }
    return text;
}
