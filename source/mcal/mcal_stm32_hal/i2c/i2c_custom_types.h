#ifndef I2C_STM_TYPES_H
#define I2C_STM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define I2C_CUSTOM_TYPES  I2C_HandleTypeDef i2c_h;

/*I2C Control register 1 (I2C_CR1)*/
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t pe         :1;/*Peripheral enable*/
        uint32_t sm_bus     :1;/*SMBus mode*/
        uint32_t res1       :1;/**/
        uint32_t smb_type   :1;/*SMBus type*/
        uint32_t enarp      :1;/*ARP enable*/
        uint32_t enpec      :1;/*PEC enable*/
        uint32_t engc       :1;/*General call enable*/
        uint32_t nostretch:1;/*Clock stretching disable (Slave mode)*/
        uint32_t start      :1;/*Start generation*/
        uint32_t stop       :1;/*Stop generation*/
        uint32_t ack        :1;/*Acknowledge enable*/
        uint32_t pos        :1;/*Acknowledge/PEC Position*/
        uint32_t pec        :1;/*Packet error checking*/
        uint32_t alert      :1;/*SMBus alert*/
        uint32_t res2       :1;/**/
        uint32_t sw_rst     :1;/*Software reset*/
        uint16_t res3       ;/**/
    };
}I2cRegControl1_t;


/*I2C Control register 2 (I2C_CR2)*/
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t freq         :6;/*Peripheral clock frequency*/
        uint32_t res1         :2;/*Reserved*/
        uint32_t iterr_en         :1;/*Error interrupt enable*/
        uint32_t itevt_en         :1;/*Event interrupt enable*/
        uint32_t itbuf_en         :1;/*Buffer interrupt enable*/
        uint32_t dma_en         :1;/*DMA requests enable*/
        uint32_t last         :1;/*DMA last transfer*/
        uint32_t res2         :19;/*Reserved,*/
    };
}I2cRegControl2_t;

/*I2C Status register 1 (I2C_SR1)*/
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t sb      :1;/*0 Start bit (Master mode*/
        uint32_t addr    :1;/*1 Address sent (master mode)/matched (slave mode)*/
        uint32_t btf     :1;/*2 Byte transfer finished*/
        uint32_t add10   :1;/*3 10-bit header sent (Master mode)*/
        uint32_t stopf   :1;/*4 Stop detection (slave mode)*/
        uint32_t res1    :1;/*5 Reserved,*/
        uint32_t rxne    :1;/*6 Data register not empty*/
        uint32_t txe     :1;/*7 Data register empty (transmitters)*/
        uint32_t berr    :1;/*8 Bus error*/
        uint32_t arlo    :1;/*9 Arbitration lost (master mode)*/
        uint32_t af      :1;/*10 Acknowledge failure*/
        uint32_t ovr :1;/*11 Overrun/Underrun*/
        uint32_t pec     :1;/*12 PEC Error in reception*/
        uint32_t res2 :1;/*13*/
        uint32_t timeo   :1;/*14 Timeout or Tlow error*/
        uint32_t smb_alert   :1;/*15 SMBus alert*/
        uint32_t res   :16;/* 16-31 SMBus alert*/
    };
}I2cRegStatus1_t;

/*I2C Status register 2 (I2C_SR2)*/
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t msl :1; /*Master/slave*/
        uint32_t busy :1;/*Bus busy*/
        uint32_t tra :1;/*Transmitter/receiver*/
        uint32_t res1 :1;/*Reserved*/
        uint32_t gen_call :1;/*General call address (Slave mode)*/
        uint32_t smb_defau_lt :1;/*SMBus device default address (Slave mode)*/
        uint32_t smb_host :1;/*SMBus host header (Slave mode)*/
        uint32_t dualf :1;/*Dual flag (Slave mode)*/
        uint32_t pec :1;/*Packet error checking register*/
        uint32_t res2 :16;/*xxxxxx*/
    };
}I2cRegStatus2_t;

typedef struct {
    bool valid;
 //   i2c_type *I2Cx;
    uint8_t num;
   // ClockBus_t clock_bus;
   // crm_periph_clock_type clock_type;
   // IRQn_Type irq_evt_n;
   // IRQn_Type irq_err_n;
}I2cInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* I2C_STM_TYPES_H */
