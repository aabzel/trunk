#ifndef MX25L6433F_REG_TYPES_H
#define MX25L6433F_REG_TYPES_H

#include "std_includes.h"
#include "mx25r6435f_const.h"

/*
  Status Register (Table 5. Status Register, Page 23)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t wip : 1; /*bit0 write in progress bit*/
        uint8_t wel : 1; /*bit1 write enable latch*/
        uint8_t bp : 4; /*bit2-5 level of protected block*/
        uint8_t qe : 1;  /*bit6 Quad Enable*/
        uint8_t srwd : 1;  /*bit7 status register write*/
    };
} Mx25l6433fStatusReg_t;

typedef union {
    uint8_t byte;
    struct {
        uint16_t ods  : 1;  /*bit0  */
        uint16_t res2 : 2; /*bit4-5  */
        uint16_t tb   : 1;   /*bit3 top/bottom selected*/
        uint16_t res2 : 2; /*bit4-5  */
        uint16_t dc   : 1;   /*bit6 Dummy Cycle*/
        uint16_t res3 : 1; /*bit7 */
    };
} Mx25l6433fRegConfiguration_t;


/*
  Security Register (Table 10, Page 51)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t otp_indicator : 1;  /**< 0 = non‑factory lock, 1 = factory lock */
        uint8_t ldso          : 1;  /**< Lock‑down Secured OTP */
        uint8_t psb           : 1;  /**< Program Suspend Status */
        uint8_t esb           : 1;  /**< Erase Suspend Status */
        uint8_t reserved1     : 1;
        uint8_t p_fail        : 1;  /**< Program Fail Flag */
        uint8_t e_fail        : 1;  /**< Erase Fail Flag */
        uint8_t reserved1     : 1;
    } ;
} Mx25l6433fRegSecurity_t;


typedef union {
    uint16_t word;
    struct {
        uint8_t memory_type;    // 20
        uint8_t memory_density; // 17
    };
}Mx25l6433fDeviceId_t;

typedef union {
    uint8_t byte[3];
    struct {
        uint8_t manufacturer_id; /* Manufacturer Identification*/
        Mx25l6433fDeviceId_t device_id ; /*Device Identification */
    }__attribute__((__packed__));
}__attribute__((__packed__)) Mx25l6433fRegIdentification_t;



#endif /* MX25L6433F_REG_TYPES_H */
