#include "i2c_custom_isr.h"

#include "i2c_application.h"
#include "i2c_mcal.h"

#ifdef HAS_AT32F413
static bool I2cEvtIRQHandlerF413(I2cHandle_t* Node) {
    bool res = false;
    flag_status ret = RESET;
    ret = i2c_flag_get(Node->I2Cx, I2C_TRMODE_FLAG);
    if(SET == ret) {
        Node->it_done = true; // real Master mode
    }
    // I2C_ADDR7F_FLAG: 0~7 bit address match flag.
    ret = i2c_flag_get(Node->I2Cx, I2C_ADDR7F_FLAG);
    if(SET == ret) {
        Node->it_done = true; // no
    }
    ret = i2c_flag_get(Node->I2Cx, I2C_ALERTF_FLAG);
    if(SET == ret) {
        Node->it_done = true;
    }

    // I2C_ADDR7F_FLAG: 0~7 bit address match flag.
    ret = i2c_flag_get(Node->I2Cx, I2C_ADDRHF_FLAG);
    if(SET == ret) {
        Node->it_done = true; // no
    }

    // I2C_STARTF_FLAG: start condition generation complete flag.
    ret = i2c_flag_get(Node->I2Cx, I2C_STARTF_FLAG);
    if(SET == ret) {
        Node->it_done = true; // real
    }
    ret = i2c_flag_get(Node->I2Cx, I2C_DIRF_FLAG);
    if(SET == ret) {
        Node->it_done = true;
    }

    ret = i2c_flag_get(Node->I2Cx, I2C_ADDR2_FLAG);
    if(SET == ret) {
        Node->it_done = true;
    }
    ret = i2c_flag_get(Node->I2Cx, I2C_GCADDRF_FLAG);
    if(SET == ret) {
        Node->it_done = true;
    }
    ret = i2c_flag_get(Node->I2Cx, I2C_DEVADDRF_FLAG);
    if(SET == ret) {
        Node->it_done = true;
    }
    ret = i2c_flag_get(Node->I2Cx, I2C_HOSTADDRF_FLAG);
    if(SET == ret) {
        Node->it_done = true;
    }
    return res;
}
#endif

bool I2cEvtIRQHandler(uint8_t num) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->it_cnt++;
        i2c_evt_irq_handler(&Node->i2c_h);
        flag_status ret = 0;

        /* i2c acknowledge failure flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_ACKFAIL_FLAG);
        if(SET == ret) {
            Node->ack_fail = true;
            Node->error_cnt++;
        }

        /* i2c transmit data buffer empty flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_TDBE_FLAG);
        if(SET == ret) {
            Node->it_done = true; //
        }
#ifdef HAS_AT32F43X
        /* i2c send interrupt status */
        ret = i2c_flag_get(Node->I2Cx, I2C_TDIS_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c 0~7 bit address match flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_ADDRF_FLAG);
        if(SET == ret) {
            Node->address_match = true;
        }
        /* i2c transmission is complete, waiting to load data */
        ret = i2c_flag_get(Node->I2Cx, I2C_TCRLD_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c slave data transmit direction */
        ret = i2c_flag_get(Node->I2Cx, I2C_SDIR_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }
#endif // HAS_AT32F43X

        /* i2c transmit data complete flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_TDC_FLAG);
        if(SET == ret) {
            Node->it_done = true; // no
        }
        /* i2c stop condition generation complete flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_STOPF_FLAG);
        if(SET == ret) {
            Node->stop_done = true; // no
        }

        /* i2c receive data buffer full flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_RDBF_FLAG);
        if(SET == ret) {
            Node->it_done = true; // real Data register is full (data received)
        }

        /* i2c bus error flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_BUSERR_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c arbitration lost flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_ARLOST_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c overflow or underflow flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_OUF_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c pec receive error flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_PECERR_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c bus busy flag transmission mode */
        ret = i2c_flag_get(Node->I2Cx, I2C_BUSYF_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        ret = i2c_flag_get(Node->I2Cx, I2C_TMOUT_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

#ifdef HAS_AT32F413
        res = I2cEvtIRQHandlerF413(Node);
#endif

        ///
        i2c_interrupt_enable(Node->I2Cx, I2C_ALL_INT, FALSE);
        res = true;
    }
    return res;
}

bool I2cErrIRQHandler(uint8_t num) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        i2c_err_irq_handler(&Node->i2c_h);
        Node->error_cnt++;

        flag_status ret = 0;

        /* i2c acknowledge failure flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_ACKFAIL_FLAG);
        if(SET == ret) {
            Node->ack_fail = true;
            // i2c_flag_clear(Node->I2Cx, I2C_ACKFAIL_FLAG);
            // i2c_refresh_txdt_register(&Node->i2c_h);
        }

        /* i2c transmit data buffer empty flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_TDBE_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }
#ifdef HAS_AT32F43X
        /* i2c send interrupt status */
        ret = i2c_flag_get(Node->I2Cx, I2C_TDIS_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c 0~7 bit address match flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_ADDRF_FLAG);
        if(SET == ret) {
            Node->address_match = true;
        }

        /* i2c transmission is complete, waiting to load data */
        ret = i2c_flag_get(Node->I2Cx, I2C_TCRLD_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c slave data transmit direction */
        ret = i2c_flag_get(Node->I2Cx, I2C_SDIR_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }
#endif // HAS_AT32F43X

        /* i2c transmit data complete flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_TDC_FLAG);
        if(SET == ret) {
            Node->it_done = true; // no
        }
        /* i2c stop condition generation complete flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_STOPF_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c receive data buffer full flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_RDBF_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c bus error flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_BUSERR_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c arbitration lost flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_ARLOST_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c overflow or underflow flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_OUF_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c pec receive error flag */
        ret = i2c_flag_get(Node->I2Cx, I2C_PECERR_FLAG);
        if(SET == ret) {
            Node->it_done = true;
        }

        /* i2c bus busy flag transmission mode */
        ret = i2c_flag_get(Node->I2Cx, I2C_BUSYF_FLAG);
        if(SET == ret) {
            Node->it_done = true; // no
        }

        res = true;
    }
    return res;
}
