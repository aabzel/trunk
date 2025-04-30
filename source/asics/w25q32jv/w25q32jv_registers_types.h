#ifndef W25Q32JV_REG_TYPES_H
#define W25Q32JV_REG_TYPES_H

#include "std_includes.h"
#include "w25q32jv_const.h"

/*see page 14 7.1 Status Registers
  Figure 4a. Status Register-1
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t busy : 1; /* bit0 WRITE IN PROGRESS   BUSY*/
        uint8_t wel : 1;  /* bit1 WRITE ENABLE LATCH*/
        uint8_t bp : 3;   /* bit2-4 BLOCK PROTECT BITS*/
        uint8_t tb : 1;   /* bit5 TOP/BOTTOM PROTECT*/
        uint8_t sec : 1;  /* bit6 SECTOR PROTECT*/
        uint8_t srp : 1;  /* bit7 STATUS REGISTER PROTECT*/
    };
} W25q32jvRegStatus_t;


/* see page 14 7.1 Status Registers
   Figure 4b. Status Register-2
  */
typedef union {
    uint8_t byte;
    struct {
        uint8_t srl : 1;  /* bit0  STATUS REGISTER Lock*/
        uint8_t qe : 1;   /* bit1  QUAD ENABLE  */
        uint8_t res : 1; /* bit10 Reserved  */
        uint8_t lb : 3;   /* bit5  SECURITY REGISTER LOCK BITS  */
        uint8_t cmp : 1;  /* bit6  COMPLEMENT PROTECT  */
        uint8_t sus : 1;  /* bit7  SUSPEND STATUS  */
    };
} W25q32jvRegStatus2_t;


/*see page 14 7.1 Status Registers*/
typedef union {
    uint8_t byte;
    struct {
        uint8_t res1 : 2; /*bit0 Reserved*/
        uint8_t wps : 1; /*bit1 Write Protect Selection*/
        uint8_t res2 : 2; /*bit10 Reserved*/
        uint8_t drv : 2; /*bit5 Output Driver Strength*/
        uint8_t res3 : 1;  /*bit7 Reserved*/
    };
} W25q32jvRegStatus3_t;


/*Universal Registers*/
typedef union {
    uint8_t byte;
    W25q32jvRegStatus_t Status1;
    W25q32jvRegStatus2_t Status2;
    W25q32jvRegStatus3_t Status3;
} W25q32jvRegUniversal_t;



#endif /* W25Q32JV_REG_TYPES_H */
