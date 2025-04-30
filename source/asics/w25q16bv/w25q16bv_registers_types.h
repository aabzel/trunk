#ifndef W25Q16BV_REG_TYPES_H
#define W25Q16BV_REG_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "w25q16bv_const.h"

/*see page 30*/
typedef union {
    uint8_t byte;
    struct {
        uint8_t res : 1; /*bit0 write in progress bit*/

    };
} RegStatus_t;


typedef union {
    uint8_t byte[2];
    uint16_t word;
    struct {
    	uint16_t res1 : 3; /*bit0 xxxxx*/
    };
} RegConfiguration_t;





#endif /* W25Q16BV_REG_TYPES_H */
