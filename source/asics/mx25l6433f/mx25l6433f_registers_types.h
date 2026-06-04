#ifndef MX25L6433F_REG_TYPES_H
#define MX25L6433F_REG_TYPES_H

#include "std_includes.h"
#include "mx25l6433f_const.h"

/*see page 30Table 5. Status Register*/
typedef union {
    uint8_t byte;
    struct {
        uint8_t wip :1; /*bit0 write in progress bit*/
        uint8_t wel :1; /*bit1 write enable latch*/
        uint8_t bp :4; /*bit2-5 level of protected block*/
        uint8_t qe :1; /*bit6 Quad Enable*/
        uint8_t srwd :1; /*bit7 status register write*/
    };
} Mx25l6433fRegStatus_t;

typedef union {
    uint8_t byte[2];
    uint16_t word;
    struct {
        uint16_t res1 :3; /*bit0 xxxxx*/
        uint16_t tb :1; /*bit3 top/bottom selected*/
        uint16_t res2 :2; /*bit4-5 xxxxx*/
        uint16_t dc :1; /*bit6 Dummy Cycle*/
        uint16_t res3 :2; /*bit7*/
        uint16_t lh_switch :1;
        uint16_t res4 :6;
    };
} Mx25l6433fRegConfiguration_t;

typedef union {
    uint16_t word;
    struct {
        uint8_t memory_type;
        uint8_t memory_density;
    };
} Mx25l6433fDeviceId_t;

typedef union {
    uint8_t byte[3];
    struct {
        uint8_t manufacturer_id; /* Manufacturer Identification*/
        Mx25l6433fDeviceId_t device_id; /*Device Identification */
    } __attribute__((__packed__));
} __attribute__((__packed__)) Mx25l6433fRegIdentification_t;

#endif /* MX25L6433F_REG_TYPES_H */
