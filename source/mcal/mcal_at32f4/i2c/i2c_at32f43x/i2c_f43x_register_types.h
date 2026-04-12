#ifndef I2C_F43X_REGISTER_TYPES_H
#define I2C_F43X_REGISTER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2c_f43x_register_const.h"

// 11.7.2 Control register2 (I2C_CTRL2)
typedef union {
    uint32_t qword;
    struct {
        uint32_t saddr   :10;  /*  Bit 9:0    Slave address sent by the master*/
        uint32_t dir     :1;   /*  Bit 10     Master data transfer direction*/
        uint32_t addr10  :1;   /*  Bit 11     Host sends 10-bit address mode enable*/
        uint32_t readh10 :1;   /*  Bit 12     10-bit address header read enable*/
        uint32_t genstart:1;   /*  Bit 13     Generate start condition*/
        uint32_t genstop :1;   /*  Bit 14     Generate stop condition*/
        uint32_t nacken  :1;   /*  Bit 15     Not acknowledge enable*/
        uint32_t cnt     :8;   /*  Bit 23:16  Transmit data counter*/
        uint32_t rlden   :1;   /*  Bit 24     Send data reload mode enable*/
        uint32_t astopen :1;   /*  Bit 25     Automatically send stop condition enable*/
        uint32_t pecten  :1;   /*  Bit 26     Request PEC transmission enable*/
        uint32_t reserved:5;   /*  Bit 31:27  Reserved*/
    };
}I2cAt32F43xRegCtrl2_t;


// see 11.7.7 Status register (I2C_STS)
typedef union {
    uint32_t qword;
    struct {
        uint32_t tdbe :1;   /*Bit 0 Transmit data buffer empty flag */
        uint32_t tdis :1;   /*Bit 1 Transmit data interrupt status */
        uint32_t rdbf :1;   /*Bit 2 Receive data buffer full flag */
        uint32_t addrhf :1;   /*Bit 3 0~7 bit address head match flag  */
        uint32_t ackfailf :1;   /*Bit 4 Acknowledge failure flag  */
        uint32_t stopf :1;    /*Bit 5 Stop condition generation complete flag */
        uint32_t tdc         :1; /*Bit 6 Data transfer complete flag*/
        uint32_t tcrld       :1; /*Bit 7 Data transfer complete, waiting for data load*/
        uint32_t buserr      :1; /*Bit 8 Bus error flag*/
        uint32_t arlost      :1; /*Bit 9 Arbitration lost flag*/
        uint32_t ouf         :1; /*Bit 10 Overrun or underrun flag*/
        uint32_t pecerr      :1; /*Bit 11 PEC receive error flag*/
        uint32_t tmout       :1; /*Bit 12 SMBus timeout flag*/
        uint32_t alertf      :1; /*Bit 13 SMBus alert flag*/
        uint32_t reserved1    :1; /*Bit 14 Reserved*/
        uint32_t busyf       :1; /*Bit 15 Bus busy flag transmission mode*/
        uint32_t sdir        :1; /*Bit 16 Slave data transfer direction*/
        uint32_t addr        :7; /*Bit 23: 17 Slave address matching value*/
        uint32_t reserved2        :8; /*Bit 31: 24 Reserved*/
    };
}I2cAt32F43xRegSts_t;


// see 11.7.8 Status clear register (I2C_CLR)
typedef union {
    uint32_t qword;
    struct {
        uint32_t reserved      :3;    /*Bit 2:0 Reserved*/
        uint32_t addrc         :1;    /*Bit 3   Clear 0~7 bit address match flag*/
        uint32_t ackfailc      :1;    /*Bit 4   Clear acknowledge failure flag*/
        uint32_t stopc         :1;    /*Bit 5   Clear stop condition generation complete flag*/
        uint32_t reserved1     :2;    /*Bit 7:6 Reserved*/
        uint32_t buserrc       :1;    /*Bit 8   Clear bus error flag*/
        uint32_t arlostc       :1;    /*Bit 9   Clear arbitration lost flag*/
        uint32_t oufc          :1;    /*Bit 10  Clear overload / underload flag*/
        uint32_t pecerrc       :1;    /*Bit 11  Clear PEC receive error flag*/
        uint32_t tmoutc        :1;    /*Bit 12  Clear SMBus timeout flag*/
        uint32_t alertc        :1;    /*Bit 13  Clear SMBus alert flag*/
        uint32_t reserved2     :18;    /*Bit 31:14 Reserved*/

    };
}I2cAt32F43xRegClr_t;

/*11.7.11 Transmit data register (I2C_TXDT)*/
typedef union {
    uint32_t qword;
    struct {
        uint32_t dt       :8;     /* Bit 7: 0 Transmit data register*/
        uint32_t reserved :24;    /* Bit 31: 8 Reserved*/
    };
}I2cAt32f43xRegTxDt_t;

#ifdef __cplusplus
}
#endif

#endif /* I2C_F43X_REGISTER_TYPES_H */
