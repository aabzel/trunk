#include "i2c_at32f43x.h"

#include "i2c_f43x_register_types.h"
#include "i2c_mcal.h"
#include "log.h"

bool i2c_at32f43x_tx_byte(I2cHandle_t* const Node, uint8_t byte_data) {
    bool res = true;
    LOG_DEBUG(I2C, "F43xTrySend:0x%02x", byte_data);
    Node->I2Cx->txdt_bit.dt = byte_data;
    return res;
}

bool i2c_at32f43x_clear_ackfail_event(I2cHandle_t* const Node) {
    bool res = true;
    LOG_DEBUG(I2C, "F43xClrAckFail");
    /* Once received NACK, the ACKFAILF is set in the I2C_STS
       register. The ACKFAILF flag is cleared by writing 1 to the ACKFAILC*/
    // Clear acknowledge failure flag
    Node->I2Cx->clr_bit.ackfailc = 1;
    return res;
}

bool i2c_at32f43x_clear_stop_event(I2cHandle_t* const Node) {
    bool res = true;
    LOG_DEBUG(I2C, "F43xClrStop");
    // Clear stop condition generation complete flag
    Node->I2Cx->clr_bit.stopc = 1;
    res = i2c_at32f43x_clear_ackfail_event(Node);
    return res;
}

bool i2c_at32f43x_clear_events(I2cHandle_t* const Node) {
    bool res = true;

    // The I2C_TXDT register can be cleared by writing 1 through software.
    // res= i2c_at32f43x_tx_byte( Node,  1);
#ifdef HAS_FSM
    if(1 <= Node->TxDataSize) {
        i2c_at32f43x_tx_byte(Node, Node->TxData[0]);
    }
#endif

    Node->I2Cx->clr_bit.alertc = 1;  //   Clear SMBus alert flag
    Node->I2Cx->clr_bit.tmoutc = 1;  //   Clear SMBus timeout flag
    Node->I2Cx->clr_bit.pecerrc = 1; //   Clear PEC receive error flag
    Node->I2Cx->clr_bit.oufc = 1;    //   Clear overload / underload flag
    Node->I2Cx->clr_bit.arlostc = 1; //   Clear arbitration lost flag
    Node->I2Cx->clr_bit.buserrc = 1; //   Clear bus error flag
    Node->I2Cx->clr_bit.addrc = 1;   //   Clear 0~7 bit address match flag

    i2c_at32f43x_clear_stop_event(Node);
    return res;
}

bool i2c_at32f43x_interrupts_disable_ll(I2cHandle_t* const Node) {
    bool res = false;
    Node->I2Cx->ctrl1_bit.errien = 0;
    Node->I2Cx->ctrl1_bit.tdcien = 0;
    Node->I2Cx->ctrl1_bit.stopien = 0;
    Node->I2Cx->ctrl1_bit.ackfailien = 0;
    Node->I2Cx->ctrl1_bit.addrien = 0;
    Node->I2Cx->ctrl1_bit.rdien = 0;
    Node->I2Cx->ctrl1_bit.tdien = 0;

    I2cInfo_t* Info = I2cGetInfo(Node->num);
    if(Info) {
        nvic_irq_disable(Info->irq_evt_n);
        nvic_irq_disable(Info->irq_err_n);
        res = true;
    }
    return res;
}

static I2cMasterTxDir_t I2cConnectivityDirToTxDir(ConnectivitDir_t direction) {
    I2cMasterTxDir_t i2c_dir = I2C_MASTER_DIR_TRANSMIT;
    switch(direction) {
    case CONNECT_DIR_TRANSMITTER:
        i2c_dir = I2C_MASTER_DIR_TRANSMIT;
        break;
    case CONNECT_DIR_RECEIVER:
        i2c_dir = I2C_MASTER_DIR_RECEIVE;
        break;
    default:
        i2c_dir = I2C_MASTER_DIR_TRANSMIT;
        break;
    }
    return i2c_dir;
}

// see Figure 11-5 Transfer sequence of I2C master transmitter
bool i2c_at32f43x_init_tx_ll(I2cHandle_t* const Node, ConnectivitDir_t direction) {
    bool res = false;
    Node->spot_chip = true;
    Node->I2Cx->ctrl2_bit.saddr = i2c_make_bus_address(Node->slave_addr, direction);
    // Automatically send stop condition Disabled (Software sends STOP condition)
    Node->I2Cx->ctrl2_bit.astopen = I2C_AUTO_STOP_DISABLE;

    switch(direction) {
    case CONNECT_DIR_TRANSMITTER: {
        LOG_DEBUG(I2C, "F43xTxSize:%u", Node->TxDataSize);
        Node->I2Cx->ctrl2_bit.rlden = 0; // Send data reload mode disable
#ifdef HAS_I2C_FSM
        Node->I2Cx->ctrl2_bit.cnt = Node->TxDataSize;
        if(Node->TxDataSize) {
            i2c_at32f43x_tx_byte(Node, Node->TxData[0]);
            Node->tx_index = 1;
        } else {
            Node->fsm_state = I2C_FSM_STATE_WAIT_TX_7BIT_ADDR;
        }
#endif
        res = true;
    } break;
    case CONNECT_DIR_RECEIVER: {
#ifdef HAS_I2C_FSM
        Node->I2Cx->ctrl2_bit.cnt = Node->RxDataSize;
#endif
        res = true;
    } break;
    default:
        res = false;
        break;
    }

    Node->I2Cx->ctrl2_bit.dir = I2cConnectivityDirToTxDir(direction);
    Node->I2Cx->ctrl2_bit.nacken = 0; // 0: Acknowledge enabled
    Node->I2Cx->ctrl2_bit.addr10 = 0;
    Node->I2Cx->ctrl2_bit.readh10 = 0;

    return res;
}

bool i2c_at32f43x_clear_rdbf_events(I2cHandle_t* const Node) {
    bool res = true;
    return res;
}
