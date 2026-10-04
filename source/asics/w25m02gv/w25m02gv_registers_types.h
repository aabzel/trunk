#ifndef W25M02GV_REG_TYPES_H
#define W25M02GV_REG_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "w25m02gv_const.h"


//8.2.3 Read JEDEC ID (9Fh)
typedef union {
    uint8_t buff[3];
    struct {
        uint8_t mfr_id;
        uint16_t device_id;
    }__attribute__((__packed__));
}__attribute__((__packed__)) JedecInfo_t;

/*
 * 7.2 Configuration Register / Status Register-2 (Volatile Writable)
 */
typedef union {
    uint8_t byte;
    struct {
    	uint8_t reserved : 3;             //bit 2:0 reserved
        uint8_t buffer_mode : 1;          //bit3  Buffer Mode
        uint8_t enable_ecc : 1;           //bit4  Enable ECC
        uint8_t status_reg1_lock : 1;     //bit5  Status Register-1 Lock
        uint8_t enter_otp_mode : 1;       //bit6  Enter OTP Mde
        uint8_t otp_data_pages_lock : 1;  //bit7  OTP Data Page Lock
    };
}w25m02gvRegConfiguration_t; //Status Register-2


/*
 * 7.3 Status Register-3 (Status Only)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t busy : 1;                //bit 0    operation in progress
        uint8_t write_enable_latch : 1;  //bit 1    write enable latch WEL
        uint8_t erase_failure : 1;       //bit 2    erase failure
        uint8_t program_failire : 1;     //bit 3    program failire
        uint8_t ecc_status : 2;          //bit 5:4  ECC status bit[1:0]
        uint8_t bbm_lut_full : 1;        //bit 6    BBM LUT Full
        uint8_t reserved : 1;            //bit 7    reserved
    };
}w25m02gvRegStatus_t;


//7.1 Protection Register / Status Register-1 (Volatile Writable, OTP lockable)
typedef union {
    uint8_t byte;
    struct {
        uint8_t srp0 : 1;                //bit 0    Status Register Protect-0
        uint8_t srp1 : 1;                //bit 0    Status Register Protect-1
        uint8_t res : 6;                //bit 7     res
    };
}w25m02gvStatusRegisterProtect_t;



/*
 * 7.1 Protection Register / Status Register-1 (Volatile Writable, OTP lockable)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t srp1 : 1;                //bit 0    Status Register Protect-1
        uint8_t write_enable_bit : 1;    //bit 1    write enable bit
        uint8_t top_buttom_prot_bit : 1; //bit 2
        uint8_t block_prot : 4;          //bit 6:3  Block Protect Bits
        uint8_t srp0 : 1;                //bit 7    Status Register Protect-0
    };
}w25m02gvRegProtection_t;

typedef union {
    uint8_t byte;
    w25m02gvRegStatus_t Status;
    w25m02gvRegProtection_t Protect;
    w25m02gvRegConfiguration_t Configuration;
} W25m02gvRegUniversal_t;

#endif /* W25M02GV_REG_TYPES_H */
