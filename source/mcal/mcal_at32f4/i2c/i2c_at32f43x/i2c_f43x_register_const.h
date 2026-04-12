#ifndef I2C_F43X_REGISTER_CONST_H
#define I2C_F43X_REGISTER_CONST_H

//see 11.7 I2C registers
typedef enum{
     OFFSET_I2C_CTRL1=0x00, /**/
     OFFSET_I2C_CTRL2=0x04, /**/
     OFFSET_I2C_OADDR1=0x08, /**/
     OFFSET_I2C_OADDR2=0x0C, /**/
     OFFSET_I2C_CLKCTRL=0x10, /**/
     OFFSET_I2C_TIMEOUT=0x14, /**/
     OFFSET_I2C_STS=0x18, /*Status register*/
     OFFSET_I2C_CLR=0x1C, /**/
     OFFSET_I2C_PEC=0x20, /**/
     OFFSET_I2C_RXDT=0x24, /**/
     OFFSET_I2C_TXDT=0x28, /**/

}I2cRegName_t;



//see 11.7.2 Control register2 (I2C_CTRL2)
typedef enum {
    I2C_AUTO_STOP_DISABLE=0,
    I2C_AUTO_STOP_ENABLE=1,
}I2cAutoStop_t;

//Master data transfer direction
typedef enum {
    I2C_MASTER_DIR_RECEIVE=1,// Receive
    I2C_MASTER_DIR_TRANSMIT=0,// Transmit
}I2cMasterTxDir_t;


typedef enum {
	I2C_7_BIT_ADDRESS=0,
	I2C_10_BIT_ADDRESS=1,
}I2cHostAddressBittness_t;







#endif /* I2C_F43X_REGISTER_CONST_H */
