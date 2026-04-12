#include "i2c_fsm_f413x.h"

#include "i2c_at32f413x_diag.h"
#include "i2c_custom_diag.h"
#include "i2c_f413x_register_types.h"
#include "i2c_fsm_diag.h"
#include "log.h"

/* order matter
   addr7f > tdbe
   rdbf >busyf
 */
bool i2c_fsm_f413x_input_get(I2cHandle_t* const Node) {
    bool res = false;
    // flag_status ret = 0;
    Node->fsm_input_cnt = 0;
    Node->fsm_input_exist = false;
    I2cAt32F413xRegSts1_t I2cSts1;
    I2cAt32F413xRegSts2_t I2cSts2;

    I2cSts1.qword = Node->I2Cx->sts1;
    I2cSts2.qword = Node->I2Cx->sts2;

    if(false == Node->fsm_input_exist) { // addr7f bigger than tdbe
        if(I2cSts1.addr7f) {
            // i2c 0~7 bit address match flag
            Node->fsm_input = I2C_FSM_INPUT_RX_ACK;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) { // priority less than addr7f
        if(I2cSts1.tdbe) {
            // Transmit data buffer empty flag
            // see Figure 11-3 Transfer sequence of slave transmitter
            Node->fsm_input = I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) { // low priotity more than busyf
        // ret = i2c_flag_get(Node->I2Cx, I2C_RDBF_FLAG);
        // Figure 11-6 Transfer sequence of master receiver
        if(I2cSts1.rdbf) {
            // I2C_RDBF_FLAG: receive data buffer full flag.
            Node->fsm_input = I2C_FSM_INPUT_RX_DATA_FULL;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts1.stopf) {
            // I2C_STOPF_FLAG: stop condition generation complete flag.
            Node->fsm_input = I2C_FSM_INPUT_STOP_SIGNAL_DONE;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts1.startf) {
            // I2C_STARTF_FLAG: start condition generation complete flag.
            Node->fsm_input = I2C_FSM_INPUT_START_DONE;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts1.ackfail) {
            // I2C_ACKFAIL_FLAG: acknowledge failure flag.
            Node->fsm_input = I2C_FSM_INPUT_ACKNOWLEDGE_FAIL;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts1.addrhf) {
            // I2C_ADDRHF_FLAG: master 9~8 bit address header match flag.
            Node->fsm_input = I2C_FSM_INPUT_ADDRH_9_8_ACK;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts1.buserr) {
            // I2C_BUSERR_FLAG: bus error flag.
            Node->fsm_input = I2C_FSM_INPUT_BUS_ERROR;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts1.arlost) {
            // I2C_ARLOST_FLAG: arbitration lost flag.
            Node->fsm_input = I2C_FSM_INPUT_ARBITRATION_LOST;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts1.ouf) {
            // I2C_OUF_FLAG: overflow or underflow flag.
            Node->fsm_input = I2C_FSM_INPUT_OVERFLOW_OR_UNDERFLOW;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts1.pecerr) {
            // I2C_PECERR_FLAG: pec receive error flag.
            Node->fsm_input = I2C_FSM_INPUT_RX_PEC;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts2.gcaddrf) {
            // I2C_GCADDRF_FLAG: general call address received flag.
            Node->fsm_input = I2C_FSM_INPUT_GENERAL_CALL_ADDRESS_RECEIVED;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) {
        if(I2cSts2.addr2f) {
            // I2C_ADDR2_FLAG: own address 2 received flag.
            Node->fsm_input = I2C_FSM_INPUT_OWN_ADDRESS_2_RX;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) { // bigger than dirf
        if(I2cSts1.tdc) {
            // I2C_TDC_FLAG: transmit data complete flag.
            Node->fsm_input = I2C_FSM_INPUT_TX_DATA_DONE;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) { // seems useless flag
        if(I2cSts2.dirf) {
            // I2C_DIRF_FLAG: transmission direction flag.
            Node->fsm_input = I2C_FSM_INPUT_TX_DIR;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) { // low priority (less rdbf)
        if(I2cSts2.busyf) {
            // I2C_BUSYF_FLAG: bus busy flag transmission mode.
            Node->fsm_input = I2C_FSM_INPUT_BUS_BUSY;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }

    if(false == Node->fsm_input_exist) { // seems useless
        if(I2cSts2.trmode) {
            // I2C_TRMODE_FLAG: transmission mode.
            Node->fsm_input = I2C_FSM_INPUT_TX_MODE;
            Node->fsm_input_cnt++;
            Node->fsm_input_exist = true;
            res = true;
        }
    }
#ifdef HAS_SMBUS
    res = i2c_fsm_inpit_smbus_get(Node);
#endif

    LOG_DEBUG(I2C, ">I2C%u:%s,All:%s%s", Node->num, I2cFsmInputToStr(Node->fsm_input),
              I2cAt32f413xRegSts1ToStr(&I2cSts1), I2cAt32f413xRegSts2ToStr(&I2cSts2));
    return res;
}

bool i2c_fsm_f413x_generate_stop(I2cHandle_t* Node) {
    bool res = false;
    if(Node) {
        /*If only one byte is received, clear the ADDR7F flag
         * and set the ACKEN and GENSTOP bit in the I2C_CTRL1 register.*/

        uint8_t rx_byte = 0xFF;
        rx_byte = i2c_data_receive(Node->I2Cx);
        LOG_DEBUG(I2C, "GenerateStop,DT:0x%02x", rx_byte);
        // i2c_ack_enable(Node->I2Cx, FALSE);
        // i2c_enable(Node->I2Cx, TRUE);
        i2c_stop_generate(Node->I2Cx);
        res = true;
    }
    return res;
}
