#include "i2c_fsm_f43x.h"

#include "i2c_at32f43x_diag.h"
#include "i2c_f43x_register_types.h"
#include "i2c_fsm_diag.h"
#include "i2c_mcal.h"
#include "log.h"

I2cFsmState_t ConnectivityDirToI2cFsmF43xState(ConnectivitDir_t direction) {
    I2cFsmState_t fsm_state = I2C_FSM_STATE_UNDEF;
    switch(direction) {
    case CONNECT_DIR_TRANSMITTER:
        fsm_state = I2C_FSM_STATE_WAIT_TX_DATA;
        break;
    case CONNECT_DIR_RECEIVER:
        fsm_state = I2C_FSM_STATE_WAIT_READ_DATA;
        break;
    default:
        fsm_state = I2C_FSM_STATE_UNDEF;
        break;
    }
    return fsm_state;
}

/*1.7.7 Status register (I2C_STS)
 * order of if matter!
 * */
bool i2c_fsm_f43x_input_get(I2cHandle_t* const Node) {
    bool res = false;
    Node->fsm_input_cnt = 0;
    Node->fsm_input_exist = false;
    I2cAt32F43xRegSts_t I2C_STS;
    I2C_STS.qword = Node->I2Cx->sts;

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.ackfailf) {
            // Acknowledge failure flag
            Node->fsm_input = I2C_FSM_INPUT_ACKNOWLEDGE_FAIL;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.stopf) {
            //  Stop condition generation complete flag
            Node->fsm_input = I2C_FSM_INPUT_STOP_SIGNAL_DONE;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.tdis) { // tdbe < tdis
            //  Transmit data interrupt status TDIS
            Node->fsm_input = I2C_FSM_INPUT_TX_DATA_INTERR_STATUS;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.rdbf) {
            //  Receive data buffer full flag RDBF
            Node->fsm_input = I2C_FSM_INPUT_RX_DATA_FULL;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.tdbe) {
            // Transmit data buffer empty flag TDBE
            Node->fsm_input = I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.addrhf) {
            // 0~7 bit address head match flag
            Node->fsm_input = I2C_FSM_INPUT_ADDR_HEAD_MATCH;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.tcrld) {
            // Data transfer complete, waiting for data load
            Node->fsm_input = I2C_FSM_INPUT_TX_DONE_WAIT_LOAD;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.tdc) {
            //  Data transfer complete flag
            Node->fsm_input = I2C_FSM_INPUT_TX_DATA_DONE;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.buserr) {
            //  Bus error flag
            Node->fsm_input = I2C_FSM_INPUT_BUS_ERROR;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.arlost) {
            //  Arbitration lost flag
            Node->fsm_input = I2C_FSM_INPUT_ARBITRATION_LOST;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.ouf) {
            //   Overrun or underrun flag
            Node->fsm_input = I2C_FSM_INPUT_OVERFLOW_OR_UNDERFLOW;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.sdir) {
            //  Slave data transfer direction
            Node->fsm_input = I2C_FSM_INPUT_SLAVE_SENDS_DATA;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.pecerr) {
            //  PEC receive error flag
            Node->fsm_input = I2C_FSM_INPUT_PEC_RX_ERROR;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.tmout) {
            //  SMBus timeout flag
            Node->fsm_input = I2C_FSM_INPUT_SMBUS_TIMEOUT;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }
    if(false == Node->fsm_input_exist) {
        if(I2C_STS.alertf) {
            // SMBus alert flag
            Node->fsm_input = I2C_FSM_INPUT_SMBUS_ALERT;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2C_STS.busyf) {
            // Bus busy flag transmission mode
            Node->fsm_input = I2C_FSM_INPUT_BUS_BUSY;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }
    if(log_level_get(I2C_FSM) <= LOG_LEVEL_NOTICE) {
        cli_printf(CRLF);
    }
    LOG_NOTICE(I2C_FSM, "->I2C%u:" VT_SETCOLOR_PINK "%s" VT_SETCOLOR_NOTICE ",All:%s", Node->num,
               I2cFsmInputToStr(Node->fsm_input), I2cAt32f43xRegStsToStr(&I2C_STS));
    return res;
}

bool i2c_fsm_f43x_generate_stop(I2cHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(I2C, "f43xGenerateStop");
    Node->I2Cx->ctrl2_bit.genstop = 1;
    Node->fsm_state = I2C_FSM_STATE_WAIT_TX_STOP;
    return res;
}
