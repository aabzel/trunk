#ifndef FLASH_CUSTOM_TYPES_H
#define FLASH_CUSTOM_TYPES_H

#include <stdint.h>

#include "flash_const.h"
#include "flash_custom_const.h"

#define FLASH_CUSTOM_TYPES

typedef union {
    uint32_t reg_val;
    struct {
        uint32_t latency : 4; /*0-3 Latency*/
        uint32_t res1 : 4;    /*7:4 Reserved,*/
        uint32_t prften : 1;  /*8 Prefetch enable*/
        uint32_t icen : 1;    /*9 Instruction cache enable*/
        uint32_t dcen : 1;    /*10 Data cache enable*/
        uint32_t icrst : 1;   /*11 Instruction cache reset*/
        uint32_t dcrst : 1;   /*12 Data cache reset*/
        uint32_t res2 : 19;   /*31:13 */
    };
} RegFlashAccessCtrl_t;

/**/
typedef union {
    uint32_t reg_val;
    struct {
        uint32_t eop : 1;    // End of operation
        uint32_t operr : 1;  // Operation error
        uint32_t res1 : 2;   //
        uint32_t wrperr : 1; // Write protection error
        uint32_t pgaerr : 1; // Programming alignment error
        uint32_t pgperr : 1; // Programming parallelism error
        uint32_t pgserr : 1; // Programming sequence error
        uint32_t rderr : 1;  // Read Protection Error (PCROP)
        uint32_t res2 : 7;
        uint32_t bsy : 1; // Busy
        uint32_t res3 : 15;
    };
} RegFlashstatus_t;

#endif /* FLASH_CUSTOM_TYPES_H  */
