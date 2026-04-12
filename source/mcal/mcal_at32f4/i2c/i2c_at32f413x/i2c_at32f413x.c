#include "i2c_at32f413x.h"

#include "i2c_f413x_register_types.h"
#include "i2c_mcal.h"
#include "log.h"

bool i2c_at32f413x_interrupts_disable_ll(I2cHandle_t* Node) {
    bool res = false;
    Node->I2Cx->ctrl2_bit.dataien = 0;
    Node->I2Cx->ctrl2_bit.evtien = 0;
    Node->I2Cx->ctrl2_bit.errien = 0;
    I2cInfo_t* Info = I2cGetInfo(Node->num);
    if(Info) {
        nvic_irq_disable(Info->irq_evt_n);
        nvic_irq_disable(Info->irq_err_n);
        res = true;
    }
    return res;
}

bool i2c_at32f413x_init_tx_ll(I2cHandle_t* const Node, ConnectivitDir_t direction) {
    bool res = false;
    i2c_enable(Node->I2Cx, FALSE);
    i2c_enable(Node->I2Cx, TRUE);
    i2c_own_address1_set(Node->I2Cx, I2C_ADDRESS_MODE_7BIT, 0);
    i2c_master_receive_ack_set(Node->I2Cx, I2C_MASTER_ACK_CURRENT); // ADDR7F
    i2c_ack_enable(Node->I2Cx, TRUE);
    Node->I2Cx->ctrl1_bit.permode = 0;
    Node->I2Cx->ctrl1_bit.acken = 1;
    //  i2c_x->ctrl1_bit.acken = new_state;
    i2c_flag_clear(Node->I2Cx, I2C_ADDR7F_FLAG);
    return res;
}

bool i2c_at32f413x_clear_stop_event(I2cHandle_t* Node) {
    bool res = false;
    I2cAt32F413xRegSts1_t I2cSts1;
    I2cAt32F413xRegSts2_t I2cSts2;
    i2c_ack_enable(Node->I2Cx, FALSE);
    I2cSts1.qword = Node->I2Cx->sts1;
    I2cSts2.qword = Node->I2Cx->sts2;
    if(0 < (I2cSts1.qword + I2cSts2.qword)) {
        res = true;
    }
    return res;
}

bool i2c_at32f413x_tx_byte(I2cHandle_t* Node, uint8_t byte_data) {
    bool res = true;
    Node->I2Cx->dt_bit.dt = byte_data;
    return res;
}

bool i2c_at32f413x_clear_start_done_event(I2cHandle_t* Node) {
    bool res = true;
    I2cAt32F413xRegSts1_t I2cSts1;
    (void)I2cSts1;
    I2cSts1.qword = Node->I2Cx->sts1;

    Node->I2Cx->dt_bit.dt = 0;
    return res;
}

/*This bit is cleared by software, or by hardware when I2CEN=0.*/
bool i2c_at32f413x_clear_ackfail_event(I2cHandle_t* Node) {
    bool res = true;
    Node->I2Cx->sts1_bit.ackfail = 0;
    return res;
}

/*RDBF flag is cleared when the DT register is read.
  The RDBF bit is not set at ARLOST event.*/
bool i2c_at32f413x_clear_rdbf_events(I2cHandle_t* Node) {
    bool res = true;
    uint8_t rx_byte = Node->I2Cx->dt_bit.dt;
    LOG_DEBUG(I2C, "RxByte:0x%x", rx_byte);
    return res;
}

bool i2c_at32f413x_clear_addr7f_flag(I2cHandle_t* Node) {
    bool res = false;
    I2cAt32F413xRegSts1_t I2cSts1;
    I2cAt32F413xRegSts2_t I2cSts2;
    I2cSts1.qword = Node->I2Cx->sts1;
    I2cSts2.qword = Node->I2Cx->sts2;
    if(0 < (I2cSts1.qword + I2cSts2.qword)) {
        res = true;
    }
    return res;
}

bool i2c_at32f413x_clear_events(I2cHandle_t* Node) {
    bool res = false;
    I2cAt32F413xRegSts1_t I2cSts1;
    I2cAt32F413xRegSts2_t I2cSts2;
    i2c_ack_enable(Node->I2Cx, FALSE);
    I2cSts1.qword = Node->I2Cx->sts1;
    I2cSts2.qword = Node->I2Cx->sts2;
    if(0 < (I2cSts1.qword + I2cSts2.qword)) {
        res = true;
    }
    i2c_at32f413x_clear_rdbf_events(Node);
    return res;
}
