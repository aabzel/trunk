#ifndef I2C_F413X_REGISTER_TYPES_H
#define I2C_F413X_REGISTER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2c_f413x_register_const.h"

/*
 * 11.5.6 Status register 1 (I2C_STS1) (Offset 0x14, Reset=0)
 */
typedef union {
    uint32_t qword;
    struct {
        uint32_t startf :1;    //Bit 0 Start condition generation complete flag
        uint32_t addr7f :1;    //Bit 1 0~7 bit address match flag
        uint32_t tdc :1;       //Bit 2 Data transfer complete flag
        uint32_t addrhf :1;    //Bit 3 Master 9~8 bit address head match flag
        uint32_t stopf :1;     //Bit 4 Stop condition generation complete flag
        uint32_t reserved1 :1; //Bit 5 Kept at its default value
        uint32_t rdbf :1;      //Bit 6 Receive data buffer full flag
        uint32_t tdbe :1;      //Bit 7 Transmit data buffer empty flag
        uint32_t buserr :1;    //Bit 8 Bus error flag
        uint32_t arlost :1;    //Bit 9 Arbitration lost flag
        uint32_t ackfail :1;   //Bit 10 Acknowledge failure flag
        uint32_t ouf :1;       //Bit 11 Overload / underload flag
        uint32_t pecerr :1;    //Bit 12 PEC receive error flag
        uint32_t reserved2 :1; //Bit 13 Kept at its default value
        uint32_t tmout :1;     //Bit 14 SMBus timeout flag
        uint32_t alertf :1;    //Bit 15 SMBus alert flag
        uint32_t reserved3 :16;//Bit 31-16 Kept at its default value
    };
}I2cAt32F413xRegSts1_t;

/*
 * 11.5.7 Status register 2 (I2C_STS2) (Offset 0x18, Reset=0)
 */
typedef union {
    uint32_t qword;
    struct {
        uint32_t trmode :1;      //Bit 0 Transmission mode
        uint32_t busyf :1;       //Bit 1 Bus busy flag transmission mode
        uint32_t dirf :1;        //Bit 2 Transmission direction flag
        uint32_t reserved1 :1;   //Bit 3 Keep at its default value.
        uint32_t gcaddrf :1;     //Bit 4 General call address reception flag
        uint32_t devaddrf :1;    //Bit 5 SMBus device address reception flag
        uint32_t hostaddrf :1;   //Bit 6 SMBus host address reception flag
        uint32_t addr2f :1;      //Bit 7 Received address 2 flag
        uint32_t pecval :8;      //Bit 15: 8 PEC value
        uint32_t reserved2 :16;  //Bit 31-16  Kept at its default value
    };
}I2cAt32F413xRegSts2_t;


#ifdef __cplusplus
}
#endif

#endif /* I2C_F413X_REGISTER_TYPES_H */
