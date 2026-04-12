#include "i2c_fsm.h"

// I2C -inter-integrated circuit

#include <stdbool.h>
#include <string.h>

//#include "c_defines_generated.h"
#include "i2c_fsm_const.h"
#include "i2c_fsm_custom.h"
#include "log.h"
#include "time_mcal.h"

#ifdef HAS_AT32F413X
#include "i2c_at32f413x.h"
#include "i2c_fsm_f413x.h"
#endif

#ifdef HAS_AT32F43X
#include "i2c_at32f43x.h"
#include "i2c_fsm_f43x.h"
#endif

static bool i2c_fsm_smbus_ctrl(I2cHandle_t* Node, bool on_off) {
    bool res = true;
#ifdef HAS_AT32F413X
    i2c_smbus_enable(Node->I2Cx, on_off);
#endif
    return res;
}

bool i2c_fsm_input_get(I2cHandle_t* const Node) {
    bool res = true;
#ifdef HAS_AT32F413X
    res = i2c_fsm_f413x_input_get(Node);
#endif

#ifdef HAS_AT32F43X
    res = i2c_fsm_f43x_input_get(Node);
#endif
    return res;
}

bool i2c_interrupts_disable_ll(I2cHandle_t* Node) {
    bool res = false;
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_interrupts_disable_ll(Node);
#endif

#ifdef HAS_AT32F43X
    res = i2c_at32f43x_interrupts_disable_ll(Node);
#endif

    return res;
}

static bool i2c_fsm_init_tx(I2cHandle_t* Node, ConnectivitDir_t direction) {
    bool res = false;
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_init_tx_ll(Node, direction);
#endif

#ifdef HAS_AT32F43X
    Node->fsm_state = ConnectivityDirToI2cFsmF43xState(direction);
    res = i2c_at32f43x_init_tx_ll(Node, direction);
#endif
    return res;
}

bool i2c_fsm_generate_stop(I2cHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(I2C_FSM, "GenerateStop");
    Node->fsm_input = I2C_FSM_INPUT_NONE;
    Node->fsm_state = I2C_FSM_STATE_WAIT_TX_STOP;
#ifdef HAS_AT32F413X
    res = i2c_fsm_f413x_generate_stop(Node);
#endif

#ifdef HAS_AT32F43X
    res = i2c_fsm_f43x_generate_stop(Node);
#endif
    Node->state_start_ms = time_get_ms32();
    return res;
}

/*-----------------algorithm--------*/

bool i2c_fsm_proc_wait_chip_addr_ack_in_ack(I2cHandle_t* Node) {
    bool res = false;
    if(Node->spot_chip) {
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        i2c_clear_addr7f_flag(Node);

        switch(Node->fsm_operation) {
        case I2C_FSM_OPERATION_CHECK_ADDR: {
            i2c_ack_enable(Node->I2Cx, FALSE);
            res = i2c_fsm_generate_stop(Node);
        } break;
        case I2C_FSM_OPERATION_WRITE:
        case I2C_FSM_OPERATION_READ_MEM: {
            i2c_ack_enable(Node->I2Cx, TRUE);
            Node->fsm_state = I2C_FSM_STATE_WAIT_TX_DATA;
            /*TDBE flag is set when the DT register is empty, and cleared
              when writing to the DT register*/
            i2c_tx_byte(Node, Node->TxData[0]);
            Node->tx_index = 1;
            res = true;
        } break;

        default:
            res = false;
            break;
        }
    } else {
        LOG_DEBUG(I2C_FSM, "NoChipAck");
        res = i2c_fsm_generate_stop(Node);
        res = false;
    }
    return res;
}

bool i2c_fsm_enable(I2cHandle_t* Node) {
    bool res = true;
    LOG_DEBUG(I2C_FSM, "Enable");
    i2c_enable(Node->I2Cx, FALSE);
    i2c_enable(Node->I2Cx, TRUE);
    i2c_fsm_smbus_ctrl(Node, false);
#ifdef HAS_AT32F413X
    i2c_master_receive_ack_set(Node->I2Cx, I2C_MASTER_ACK_CURRENT);
#endif
    i2c_ack_enable(Node->I2Cx, TRUE);
    return res;
}

static I2cFsmState_t i2c_fsm_start_state(uint8_t number) {
    I2cFsmState_t state = I2C_FSM_STATE_WAIT_START1;
    switch(number) {
    case 1:
        state = I2C_FSM_STATE_WAIT_START1;
        break;
    case 2: {
        state = I2C_FSM_STATE_WAIT_START2;
    } break;
    default:
        break;
    }
    return state;
}

bool i2c_fsm_reinit_one(uint8_t num) {
    bool res = false;
    LOG_DEBUG(I2C_FSM, "I2C%u,Init", num);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        const I2cInfo_t* Info = I2cGetInfo(num);
        if(Info) {
#ifdef HAS_AT32F413
            crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
            gpio_pin_remap_config(I2C1_MUX + 2, TRUE);
#endif
            i2c_reset(Node->I2Cx);
            crm_periph_clock_enable(Info->clock_type, TRUE);
            I2cClkCtrl_t ClkCtrl;
            ClkCtrl.qword = 0x40E02C2C;
#ifdef HAS_AT32F413
            ClkCtrl.qword = 100000; // APB1:50MHz 107.7 kHz 0x40E02C2C Works fine!
#endif
            i2c_init(Node->I2Cx, 0x00, ClkCtrl.qword);
            i2c_enable(Node->I2Cx, TRUE);

            // uint8_t rx_byte = i2c_data_receive(Node->I2Cx);
            // LOG_DEBUG(I2C_FSM, "Init,DT:0x%02x",rx_byte);
            res = true;
            Node->init_done = true;
        } else {
            LOG_ERROR(I2C_FSM, "NoInfo");
        }
        /* reset i2c peripheral */
    } else {
        LOG_ERROR(I2C_FSM, "NoNode");
    }

    /* i2c peripheral enable */
    return res;
}

static ConnectivitDir_t I2cStartNumberToConnectivityDirection(uint8_t number) {
    ConnectivitDir_t direction = CONNECT_DIR_UNDEF;
    switch(number) {
    case 1:
        direction = CONNECT_DIR_TRANSMITTER;
        break;
    case 2:
        direction = CONNECT_DIR_RECEIVER;
        break;
    default:
        break;
    }
    return direction;
}

bool i2c_fsm_generate_start(I2cHandle_t* Node, uint8_t number) {
    bool res = true;
    LOG_DEBUG(I2C_FSM, "GenerateStart%u", number);

#ifdef HAS_AT32F413
    if(2 == number) {
        res = i2c_fsm_reinit_one(Node->num);
    }
#endif
    Node->fsm_state = i2c_fsm_start_state(number);
    res = i2c_fsm_init_tx(Node, I2cStartNumberToConnectivityDirection(number));

    Node->fsm_input = I2C_FSM_INPUT_NONE;
    res = i2c_fsm_smbus_ctrl(Node, false);

    i2c_start_generate(Node->I2Cx);
    Node->state_start_ms = time_get_ms32();
    return res;
}

// The goal of busy to move in idle
bool i2c_fsm_proc_frame_wait_busy(I2cHandle_t* Node) {
    bool res = false;
    switch(Node->fsm_input) {
    case I2C_FSM_INPUT_GENERATE_START: {
        Node->fsm_state = I2C_FSM_STATE_IDLE;
        // Node->fsm_input = I2C_FSM_INPUT_GENERATE_START;
    } break;

    case I2C_FSM_INPUT_NONE: {
        res = true;
        Node->fsm_state = I2C_FSM_STATE_IDLE;
        // Node->fsm_input = I2C_FSM_INPUT_GENERATE_START;
    } break;

    case I2C_FSM_INPUT_BUS_BUSY: {
        res = true;
        Node->fsm_state = I2C_FSM_STATE_WAIT_BUSY;
    } break;
    case I2C_FSM_INPUT_START_DONE: {
    } break;
    case I2C_FSM_INPUT_STOP_SIGNAL_DONE: {
    } break;
    case I2C_FSM_INPUT_RX_ACK: {
    } break;
    case I2C_FSM_INPUT_TX_DATA_DONE: {
    } break;
    case I2C_FSM_INPUT_TX_MODE: {
    } break;
    case I2C_FSM_INPUT_TX_DIR: {
    } break;
    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY: {
    } break;
    case I2C_FSM_INPUT_ACKNOWLEDGE_FAIL: {
    } break;
    case I2C_FSM_INPUT_RX_DATA_FULL: {
    } break;
    case I2C_FSM_INPUT_BUS_ERROR: {
    } break;
    case I2C_FSM_INPUT_ADDRH_9_8_ACK: {
    } break;
    case I2C_FSM_INPUT_OVERFLOW_OR_UNDERFLOW: {
    } break;
    case I2C_FSM_INPUT_RX_PEC: {
    } break;
    case I2C_FSM_INPUT_SMBUS_TIMEOUT: {
    } break;
    case I2C_FSM_INPUT_SMBUS_ALERT: {
    } break;
    case I2C_FSM_INPUT_ARBITRATION_LOST: {
    } break;
    case I2C_FSM_INPUT_GENERAL_CALL_ADDRESS_RECEIVED: {
    } break;
    case I2C_FSM_INPUT_SMBUS_DEVICE_ADDRESS_RX: {
    } break;
    case I2C_FSM_INPUT_SMBUS_HOST_ADDRESS_RX: {
    } break;
    case I2C_FSM_INPUT_OWN_ADDRESS_2_RX: {
    } break;

    default: {
        LOG_ERROR(I2C_FSM, "WaitBusyUnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
    } break;
    }
    return res;
}
// Node->fsm_input=I2C_FSM_INPUT_NONE

bool i2c_fsm_proc_frame_idle(I2cHandle_t* Node) {
    bool res = false;
    switch(Node->fsm_input) {
    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY: {
        LOG_DEBUG(I2C_FSM, "ProcIdleTDBE");
        res = i2c_clear_events(Node);
        res = i2c_fsm_generate_start(Node, 1);
    } break;

    case I2C_FSM_INPUT_NONE:
    case I2C_FSM_INPUT_GENERATE_START: {
        res = i2c_fsm_generate_start(Node, 1);
    } break;

    case I2C_FSM_INPUT_RX_DATA_FULL: {
        LOG_DEBUG(I2C_FSM, "ProcIdleRDBF");
        res = i2c_clear_rdbf_events(Node);
        res = i2c_fsm_generate_start(Node, 1);
    } break;

    case I2C_FSM_INPUT_START_DONE: {
        res = i2c_start_done_clear(Node);
    } break;

    case I2C_FSM_INPUT_TX_MODE: {
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        // res = i2c_fsm_generate_stop(Node);
        res = true;
    } break;

    case I2C_FSM_INPUT_TX_DATA_INTERR_STATUS: {
        LOG_DEBUG(I2C_FSM, "ProcIdleTDIS");
        res = i2c_clear_events(Node);
    } break;

    case I2C_FSM_INPUT_BUS_ERROR: {
        LOG_DEBUG(I2C_FSM, "ProcIdleBusError");
        res = i2c_init_one(Node->num);
    } break;

    case I2C_FSM_INPUT_TIME_OUT: {
        LOG_DEBUG(I2C_FSM, "ProcIdleTimeOut");
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        res = true;
    } break;

    case I2C_FSM_INPUT_ACKNOWLEDGE_FAIL: {
        LOG_DEBUG(I2C_FSM, "ProcIdleACKFAIL");
        res = i2c_clear_ackfail_event(Node);
    } break;

    default:
        LOG_ERROR(I2C_FSM, "IdleUnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
        res = i2c_clear_events(Node);
        break;
    }
    return res;
}

static bool i2c_write_address(I2cHandle_t* Node) {
    bool res = true;
    uint8_t chip_address = i2c_compose_write_address(Node->slave_addr);
    LOG_DEBUG(I2C_FSM, "SetWriteAddr:0x%x", chip_address);
    Node->fsm_state = I2C_FSM_STATE_WAIT_TX_7BIT_ADDR;
    i2c_tx_byte(Node, chip_address);
    return res;
}

//
static bool i2s_fsm_proc_wait_start1_done_get_done(I2cHandle_t* Node) {
    bool res = false;
    Node->fsm_input = I2C_FSM_INPUT_NONE;
    switch(Node->fsm_operation) {
    case I2C_FSM_OPERATION_EMPTY: {
        res = i2c_fsm_generate_stop(Node);
    } break;

    case I2C_FSM_OPERATION_WRITE:
    case I2C_FSM_OPERATION_READ_MEM:
    case I2C_FSM_OPERATION_CHECK_ADDR: {
        // i2c_chip_address_ack_enable(Node);
        Node->fsm_state = I2C_FSM_STATE_WAIT_TX_7BIT_ADDR;
        res = i2c_write_address(Node);
    } break;

    default:
        res = false;
        break;
    }
    Node->state_start_ms = time_get_ms32();
    return res;
}

static bool i2s_fsm_proc_wait_start2_done_get_done(I2cHandle_t* Node) {
    bool res = false;
    Node->fsm_input = I2C_FSM_INPUT_NONE;
    switch(Node->fsm_operation) {
    case I2C_FSM_OPERATION_READ_MEM: {
        uint8_t chip_addr = i2c_compose_read_address(Node->slave_addr);
        LOG_DEBUG(I2C_FSM, "SetChipReadAddr:0x%x", chip_addr);
        Node->fsm_state = I2C_FSM_STATE_WAIT_TX_CHIP_READ_ADDR;
        i2c_tx_byte(Node, chip_addr);
    } break;
    default: {
        LOG_ERROR(I2C_FSM, "UndefOp%u", Node->fsm_operation);
        res = false;
    } break;
    }
    Node->state_start_ms = time_get_ms32();
    return res;
}

bool i2c_fsm_proc_frame_wait_start1_done(I2cHandle_t* Node) {
    bool res = false;

    uint32_t cur_ms = time_get_ms32();
    uint32_t stop_wait_ms = cur_ms - Node->state_start_ms;
    if(I2C_FSM_STOP_WAIT_TIMEOUT_MS < stop_wait_ms) {
        Node->fsm_input = I2C_FSM_INPUT_START_SIGNAL_TIMEOUT;
    }
    switch(Node->fsm_input) {
    case I2C_FSM_INPUT_START_DONE: {
        Node->fsm_input = I2C_FSM_INPUT_START_DONE;
        i2c_clear_events(Node);
        res = i2s_fsm_proc_wait_start1_done_get_done(Node);
    } break;

    case I2C_FSM_INPUT_START_SIGNAL_TIMEOUT:
        LOG_DEBUG(I2C_FSM, "StartTimeOut");
        break;
    case I2C_FSM_INPUT_STOP_SIGNAL_DONE: {
    } break;
    case I2C_FSM_INPUT_RX_PEC: {
    } break;
    case I2C_FSM_INPUT_TX_DATA_DONE: {
    } break;
    case I2C_FSM_INPUT_RX_DATA_FULL: {
    } break;
    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY: {
    } break;
    case I2C_FSM_INPUT_BUS_ERROR: {
    } break;
    case I2C_FSM_INPUT_GENERATE_START: {
    } break;
    case I2C_FSM_INPUT_RX_ACK: {
    } break;
    case I2C_FSM_INPUT_NONE: {
    } break;
    case I2C_FSM_INPUT_ADDRH_9_8_ACK: {
    } break;
    case I2C_FSM_INPUT_ARBITRATION_LOST: {
    } break;
    case I2C_FSM_INPUT_ACKNOWLEDGE_FAIL: {
    } break;
    case I2C_FSM_INPUT_OVERFLOW_OR_UNDERFLOW: {
    } break;
    case I2C_FSM_INPUT_SMBUS_TIMEOUT: {
    } break;
    case I2C_FSM_INPUT_SMBUS_ALERT: {
    } break;
    case I2C_FSM_INPUT_TX_MODE: {
    } break;
    case I2C_FSM_INPUT_BUS_BUSY: { // Node->fsm_state=I2C_FSM_SATE_WAIT_BUSY;
        // This is for a long time
        // res = i2c_fsm_generate_stop(Node);
    } break;
    case I2C_FSM_INPUT_TX_DIR: {
    } break;
    case I2C_FSM_INPUT_GENERAL_CALL_ADDRESS_RECEIVED: {
    } break;
    case I2C_FSM_INPUT_SMBUS_DEVICE_ADDRESS_RX: {
    } break;
    case I2C_FSM_INPUT_SMBUS_HOST_ADDRESS_RX: {
    } break;
    case I2C_FSM_INPUT_OWN_ADDRESS_2_RX: {
    } break;

    default: {
        LOG_ERROR(I2C_FSM, "WaitStart1UnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
    } break;
    }
    return res;
}

bool i2c_fsm_proc_frame_wait_start2_done(I2cHandle_t* Node) {
    bool res = false;

    uint32_t cur_ms = time_get_ms32();
    uint32_t stop_wait_ms = cur_ms - Node->state_start_ms;
    if(I2C_FSM_STOP_WAIT_TIMEOUT_MS < stop_wait_ms) {
        Node->fsm_input = I2C_FSM_INPUT_START_SIGNAL_TIMEOUT;
    }

    switch(Node->fsm_input) {
    case I2C_FSM_INPUT_START_SIGNAL_TIMEOUT:
        LOG_ERROR(I2C_FSM, "Start2TimeOut");
        res = i2c_fsm_generate_stop(Node);
        break;
    case I2C_FSM_INPUT_START_DONE: {
        res = i2s_fsm_proc_wait_start2_done_get_done(Node);
    } break;
    default: {
        LOG_ERROR(I2C_FSM, "WaitStart2UnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
    } break;
    }
    return res;
}

bool i2c_fsm_proc_frame_wait_tx_data_done(I2cHandle_t* Node) {
    bool res = false;

    uint32_t cur_ms = time_get_ms32();
    uint32_t stop_wait_ms = cur_ms - Node->state_start_ms;
    if(I2C_FSM_MEM_ADDRESS_ACK_WAIT_TIMEOUT_MS < stop_wait_ms) {
        Node->fsm_input = I2C_FSM_INPUT_RX_ACK_TIMEOUT;
    }

    switch(Node->fsm_input) {

    case I2C_FSM_INPUT_BUS_BUSY: {
        LOG_DEBUG(I2C_FSM, "WaitTxDataProcBusBusy");
        res = true;
    } break;

    case I2C_FSM_INPUT_STOP_SIGNAL_DONE: {
        res = i2c_clear_stop_event(Node);
    } break;

    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY: {
        LOG_DEBUG(I2C_FSM, "ProcTxDataTDBE");
        if(Node->tx_index < Node->TxDataSize) {
            res = i2c_tx_byte(Node, Node->TxData[Node->tx_index]);
            Node->tx_index++;
            res = true;
        } else {
            if(I2C_FSM_OPERATION_WRITE == Node->fsm_operation) {
                res = i2c_fsm_generate_stop(Node);
            } else if(I2C_FSM_OPERATION_READ_MEM == Node->fsm_operation) {
                i2c_clear_events(Node);
                res = i2c_fsm_generate_start(Node, 2);
            } else {
                res = false;
            }
        }
    } break;

    case I2C_FSM_INPUT_TX_DATA_INTERR_STATUS: {
        LOG_DEBUG(I2C_FSM, "ProcTDIS");
        if(Node->tx_index < Node->TxDataSize) {
            res = i2c_tx_byte(Node, Node->TxData[Node->tx_index]);
            Node->tx_index++;
            res = true;
        } else {
            if(I2C_FSM_OPERATION_WRITE == Node->fsm_operation) {
                res = i2c_fsm_generate_stop(Node);
            } else if(I2C_FSM_OPERATION_READ_MEM == Node->fsm_operation) {
                i2c_clear_events(Node);
                res = i2c_fsm_generate_start(Node, 2);
            } else {
                res = false;
            }
        }
    } break;

    case I2C_FSM_INPUT_RX_ACK_TIMEOUT: {
        res = i2c_fsm_generate_start(Node, 2);
    } break;

    default: {
        LOG_ERROR(I2C_FSM, "WaitTxDataUnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
        res = false;
    } break;
    }
    return res;
}

bool i2c_fsm_proc_frame_wait_chip_read_addr_done(I2cHandle_t* Node) {
    bool res = false;

    uint32_t cur_ms = time_get_ms32();
    uint32_t stop_wait_ms = cur_ms - Node->state_start_ms;
    if(I2C_FSM_CHIP_ADDR_ACK_WAIT_TIMEOUT_MS < stop_wait_ms) {
        Node->fsm_input = I2C_FSM_INPUT_CHIP_ADDR_ACK_TIMEOUT;
    }
    switch(Node->fsm_input) {
    case I2C_FSM_INPUT_BUS_BUSY: {
        res = true;
    } break;

    case I2C_FSM_INPUT_RX_ACK: {
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        i2c_ack_enable(Node->I2Cx, FALSE);
        if(1 == Node->RxDataSize) {
            /*If only one byte is received, clear the ADDR7F flag
             * and set the ACKEN and GENSTOP bit in the I2C_CTRL1 register.*/

            /*
            When the second-to-last byte is being read, clear the ACKEN bit
            and set the GENSTOP bit in the I2C_CTRL1 register to generate
            a Stop condition.*/

            /*I2C_STS1_ADDR7F = 1,
             * clear the I2C_CTRL1_ACKEN bit, and
               reading STS1 and then STS2 will clear the event, then
               set the I2C_CTRL1_GENSTOP bit = 1.*/
            // i2c_flag_clear(Node->I2Cx, I2C_ADDR7F_FLAG);

            i2c_clear_events(Node);
            i2c_ack_enable(Node->I2Cx, FALSE);

            res = i2c_fsm_generate_stop(Node);
        } else {
            Node->fsm_state = I2C_FSM_STATE_WAIT_READ_DATA;
        }
        res = true;
    } break;

    case I2C_FSM_INPUT_CHIP_ADDR_ACK_TIMEOUT: {
        LOG_DEBUG(I2C_FSM, "ChipAckTimeOut");
        i2c_ack_enable(Node->I2Cx, FALSE);
        res = i2c_fsm_generate_stop(Node);
    } break;

    case I2C_FSM_INPUT_TX_MODE: {
        // LOG_DEBUG(I2C_FSM, "WaitTxAsicReadAddrMasterMode");
        res = true;
    } break;

    default: {
        LOG_ERROR(I2C_FSM, "WaitTxAsicReadAddrUnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
    } break;
    }
    return res;
}

bool i2c_fsm_proc_frame_wait_read_data(I2cHandle_t* Node) {
    bool res = false;

    uint32_t cur_ms = time_get_ms32();
    uint32_t stop_wait_ms = cur_ms - Node->state_start_ms;
    if(I2C_FSM_CHIP_READ_DATA_TIMEOUT_MS < stop_wait_ms) {
        Node->fsm_input = I2C_FSM_INPUT_READ_DATA_TIMEOUT;
    }

    switch(Node->fsm_input) {
    case I2C_FSM_INPUT_RX_DATA_FULL: {
        /*
          RDBF Receive data buffer full
          RDBF flag is cleared when the DT register is read.
          The RDBF bit is not set at ARLOST event

          When the second-to-last byte is being read, clear the ACKEN bit
          and set the GENSTOP bit in the I2C_CTRL1 register to generate
          a Stop condition.*/
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        // i2c_enable(Node->I2Cx, FALSE);
        if(Node->rx_index < Node->RxDataSize) {
            uint8_t rx_byte = i2c_data_receive(Node->I2Cx);
            // i2c_enable(Node->I2Cx, TRUE);
            LOG_DEBUG(I2C_FSM, "RxByte:0x%02x", rx_byte);
            Node->RxData[Node->rx_index] = rx_byte;
            LOG_DEBUG(I2C_FSM, "RxData[%u]=0x%02x", Node->rx_index, rx_byte);
            Node->rx_index++;
        }
        if(Node->RxDataSize <= Node->rx_index) {
            res = i2c_fsm_generate_stop(Node);
        }
    } break;

    case I2C_FSM_INPUT_READ_DATA_TIMEOUT: {
        res = i2c_fsm_generate_stop(Node);
    } break;

    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY:
    case I2C_FSM_INPUT_BUS_BUSY: {
        res = true;
    } break;

    default: {
        LOG_ERROR(I2C_FSM, "WaitReadDataUnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
    } break;
    }

    return res;
}

bool i2c_fsm_proc_frame_wait_tx_7bitaddr_done(I2cHandle_t* Node) {
    bool res = false;

    uint32_t cur_ms = time_get_ms32();
    uint32_t stop_wait_ms = cur_ms - Node->state_start_ms;
    if(I2C_FSM_CHIP_ADDR_ACK_WAIT_TIMEOUT_MS < stop_wait_ms) {
        Node->fsm_input = I2C_FSM_INPUT_CHIP_ADDR_ACK_TIMEOUT;
    }

    switch(Node->fsm_input) {
    case I2C_FSM_INPUT_RX_DATA_FULL: {
        LOG_DEBUG(I2C_FSM, "WaitWrAddrAckProcRDBF");
        res = i2c_fsm_generate_stop(Node);
    } break;

    case I2C_FSM_INPUT_RX_ACK: {
        LOG_DEBUG(I2C_FSM, "SpotChip!");
        Node->spot_chip = true;
#ifdef HAS_AT32F413X
        i2c_flag_clear(Node->I2Cx, I2C_ADDR7F_FLAG);
#endif
    } break;

    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY: {
        /*Transmit data buffer empty
        The data has been moved from the DT register to the
        shift register. The data register is empty now.*/
        LOG_DEBUG(I2C_FSM, "ProcTDBE");
#ifdef HAS_AT32F413X
        res = i2c_fsm_proc_wait_chip_addr_ack_in_ack(Node);
#endif

#ifdef HAS_AT32F43X
        // res = i2c_tx_byte(Node,Node->TxData[0]);
        // Node->tx_index = 1;
        // Node->fsm_state = I2C_FSM_STATE_WAIT_TX_DATA ;
        res = true;
        if(I2C_FSM_OPERATION_CHECK_ADDR == Node->fsm_operation) {
            res = i2c_fsm_generate_stop(Node);
        }
#endif
    } break;

    case I2C_FSM_INPUT_TX_DATA_INTERR_STATUS: {
        LOG_DEBUG(I2C_FSM, "ProcTDIS");
        res = i2c_tx_byte(Node, Node->TxData[0]);
        Node->tx_index = 1;
        Node->fsm_state = I2C_FSM_STATE_WAIT_TX_DATA;
    } break;

    case I2C_FSM_INPUT_ACKNOWLEDGE_FAIL: {
        LOG_DEBUG(I2C_FSM, "ProcNak!");
        Node->spot_chip = false;
#ifdef HAS_AT32F413X
        Node->I2Cx->sts1_bit.ackfail = 0;
        i2c_ack_enable(Node->I2Cx, FALSE);
#endif
        res = i2c_fsm_generate_stop(Node);
    } break;

    case I2C_FSM_INPUT_CHIP_ADDR_ACK_TIMEOUT: {
        LOG_DEBUG(I2C_FSM, "ChipAckTimeOut");
        res = i2c_fsm_generate_stop(Node);
    } break;

    case I2C_FSM_INPUT_TX_DATA_DONE: {
        LOG_DEBUG(I2C_FSM, "ProcTxDatDone");
        res = i2c_fsm_generate_stop(Node);
    } break;

    case I2C_FSM_INPUT_TX_MODE: {
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        res = true;
    } break;
    case I2C_FSM_INPUT_BUS_BUSY: {
        res = true;
    } break;
#if 0
    case I2C_FSM_INPUT_RX_PEC:
    case I2C_FSM_INPUT_STOP_SIGNAL_DONE:
    case I2C_FSM_INPUT_BUS_ERROR:
    case I2C_FSM_INPUT_GENERATE_START:
    case I2C_FSM_INPUT_NONE:
    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY:
    case I2C_FSM_INPUT_ADDRH_9_8_ACK:
    case I2C_FSM_INPUT_OVERFLOW_OR_UNDERFLOW:
    case I2C_FSM_INPUT_SMBUS_TIMEOUT:
    case I2C_FSM_INPUT_ARBITRATION_LOST:
    case I2C_FSM_INPUT_TX_DIR:
    case I2C_FSM_INPUT_GENERAL_CALL_ADDRESS_RECEIVED:
    case I2C_FSM_INPUT_SMBUS_DEVICE_ADDRESS_RX:
    case I2C_FSM_INPUT_SMBUS_ALERT:
    case I2C_FSM_INPUT_SMBUS_HOST_ADDRESS_RX:
    case I2C_FSM_INPUT_OWN_ADDRESS_2_RX:
    case I2C_FSM_INPUT_START_DONE: {
    }break;
#endif

    default: {
        LOG_ERROR(I2C_FSM, "WaitTxAddrUnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
    } break;
    }
    return res;
}

bool i2c_fsm_proc_frame_wait_stop_done(I2cHandle_t* Node) {
    bool res = false;

    uint32_t cur_ms = time_get_ms32();
    uint32_t stop_wait_ms = cur_ms - Node->state_start_ms;
    if(I2C_FSM_STOP_WAIT_TIMEOUT_MS < stop_wait_ms) {
        Node->fsm_input = I2C_FSM_INPUT_STOP_SIGNAL_TIMEOUT;
    }

    switch(Node->fsm_input) {

    case I2C_FSM_INPUT_ACKNOWLEDGE_FAIL: {
        LOG_DEBUG(I2C_FSM, "ProcNAK");
        Node->spot_chip = false;
        res = i2c_clear_ackfail_event(Node);
    } break;

    case I2C_FSM_INPUT_STOP_SIGNAL_DONE: {
        LOG_DEBUG(I2C_FSM, "ProcStopDone");
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        res = i2c_clear_stop_event(Node);
        Node->loop = false;
    } break;

    case I2C_FSM_INPUT_STOP_SIGNAL_TIMEOUT: {
        LOG_DEBUG(I2C_FSM, "WaitStopTimeOut");
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        res = true;
        Node->loop = false;
    } break;

    case I2C_FSM_INPUT_RX_DATA_FULL: {
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        if(Node->rx_index < Node->RxDataSize) {
            uint8_t rx_byte = i2c_data_receive(Node->I2Cx);
            LOG_DEBUG(I2C_FSM, "DT:0x%02x", rx_byte);
            Node->RxData[Node->rx_index] = rx_byte;
            LOG_DEBUG(I2C_FSM, "RxData[%u]=0x%02x", Node->rx_index, rx_byte);
            Node->rx_index++;
        }
        res = false;
    } break;

    case I2C_FSM_INPUT_BUS_BUSY: {
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        res = false;
    } break;

    case I2C_FSM_INPUT_TX_MODE: {
        res = i2c_fsm_generate_stop(Node);
    } break;

    case I2C_FSM_INPUT_START_DONE: {
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        res = false;
        LOG_ERROR(I2C_FSM, "Unexp,Start,Done");
        // Node->loop = false;
    } break;

    case I2C_FSM_INPUT_NONE: {
        //   Node->loop = false;
        res = true;
        // Node->loop = false;
    } break;

    case I2C_FSM_INPUT_RX_ACK: {
        // Node->loop = false;
    } break;

    case I2C_FSM_INPUT_RX_PEC: {
        // Node->loop = false;
    } break;

    case I2C_FSM_INPUT_TX_DATA_DONE: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY: {
        // Node->loop = false;
    } break;

    case I2C_FSM_INPUT_BUS_ERROR: {
        // Node->loop = false;
    } break;

    case I2C_FSM_INPUT_GENERATE_START: {
        // Node->loop = false;
    } break;

    case I2C_FSM_INPUT_ADDRH_9_8_ACK: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_ARBITRATION_LOST: {
        // Node->loop = false;
    } break;

    case I2C_FSM_INPUT_OVERFLOW_OR_UNDERFLOW: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_SMBUS_TIMEOUT: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_SMBUS_ALERT: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_TX_DIR: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_GENERAL_CALL_ADDRESS_RECEIVED: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_SMBUS_DEVICE_ADDRESS_RX: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_SMBUS_HOST_ADDRESS_RX: {
        //  Node->loop = false;
    } break;

    case I2C_FSM_INPUT_OWN_ADDRESS_2_RX: {
        //  Node->loop = false;
    } break;

    default: {
        LOG_ERROR(I2C_FSM, "WaitStopUnexpIn,%s", I2cFsmInputToStr(Node->fsm_input));
    } break;
    }
    return res;
}

#ifdef HAS_SMBUS
static bool i2c_fsm_inpit_smbus_get(I2cHandle_t* const Node) {
    bool res = false;
    // I2C_TMOUT_FLAG: smbus timeout flag.
    if(false == Node->fsm_input_exist) {

        ret = i2c_flag_get(Node->I2Cx, I2C_TMOUT_FLAG);
        if(SET == ret) {
            Node->fsm_input = I2C_FSM_INPUT_SMBUS_TIMEOUT;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {

        // I2C_ALERTF_FLAG: smbus alert flag.
        ret = i2c_flag_get(Node->I2Cx, I2C_ALERTF_FLAG);
        if(SET == ret) {
            Node->fsm_input = I2C_FSM_INPUT_SMBUS_ALERT;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {

        // I2C_DEVADDRF_FLAG: smbus device address received flag.
        ret = i2c_flag_get(Node->I2Cx, I2C_DEVADDRF_FLAG);
        if(SET == ret) {
            Node->fsm_input = I2C_FSM_INPUT_SMBUS_DEVICE_ADDRESS_RX;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {

        // I2C_HOSTADDRF_FLAG: smbus host address received flag.
        ret = i2c_flag_get(Node->I2Cx, I2C_HOSTADDRF_FLAG);
        if(SET == ret) {
            Node->fsm_input = I2C_FSM_INPUT_SMBUS_HOST_ADDRESS_RX;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }
    return res;
}
#endif

#define I2C_FSM_GET_FLAG(FLAG, ENUM)                                                                                   \
    do {                                                                                                               \
        ret = i2c_flag_get(Node->I2Cx, FLAG);                                                                          \
        if(SET == ret) {                                                                                               \
            Node->fsm_input = ENUM;                                                                                    \
            Node->fsm_input_cnt++;                                                                                     \
            res = true;                                                                                                \
        }                                                                                                              \
    } while(0);

bool i2c_fsm_proc_timeout(I2cHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(I2C_FSM, "I2C%u,TimeOut", Node->num);
    Node->fsm_input = I2C_FSM_INPUT_TIME_OUT;
    Node->loop = false;
    return res;
}

#if 0
bool i2c_fsm_check_addr_cus(uint8_t num, uint8_t i2c_addr) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {

        uint32_t start = 0;
        uint32_t diff = 0;
        flag_status ret = 0;
        i2c_master_receive_ack_set(Node->I2Cx, I2C_MASTER_ACK_NEXT);
        i2c_ack_enable(Node->I2Cx, TRUE);
        res = true;
        Node->ack_done = false;
        Node->ack_fail = false;
        i2c_start_generate(Node->I2Cx);
        while(1) {
            ret = i2c_fsm_flag_get(Node->I2Cx, I2C_STARTF_FLAG);
            if(SET == ret) {
 break;
            }
        }

        i2c_tx_byte(Node, i2c_fsm_addr);

        // i2c_fsm_7bit_address_send(Node->I2Cx,   i2c_fsm_addr, I2C_DIRECTION_RECEIVE);

        start = time_get_ms32();

        while(1) {
            ret = i2c_fsm_flag_get(Node->I2Cx, I2C_ADDR7F_FLAG);
            if(SET == ret) {
 break;
            }
            uint32_t cur = time_get_ms32();
            diff = cur - start;
            if(50 < diff) {
                res = false;
 break;
            }
        }

        if(Node->ack_fail) {
            res = false;
            res = i2c_fsm_wait_ack_ll(Node, 50);
        }

        i2c_stop_generate(Node->I2Cx);

        start = time_get_ms32();
        while(1) {
            ret = i2c_fsm_flag_get(Node->I2Cx, I2C_STOPF_FLAG);
            if(SET == ret) {
                  break;
            }
            uint32_t cur = time_get_ms32();
            diff = cur - start;
            if(50 < diff) {
                // res = false;
                  break;
            }
        }
    }
    return res;
}
#endif
