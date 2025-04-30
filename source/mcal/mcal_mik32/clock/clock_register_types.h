#ifndef CLOCK_REGISTER_TYPES_H
#define CLOCK_REGISTER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/* Register for enabling clocking of devices on the AHB bus Each
   bit corresponds to a device:   */
typedef union {
    uint32_t dword;
    struct{
        uint32_t cpu :1;      /*  bit0 CPU     */
        uint32_t eeprom :1;   /*  bit1 EEPROM  */
        uint32_t ram :1;      /*  bit2 RAM     */
        uint32_t spifi :1;    /*  bit3 SPIFI   */
        uint32_t tcb :1;      /*  bit4 Test control Block     */
        uint32_t dma :1;      /*  bit5 DMA     */
        uint32_t cryp :1;     /*  bit6 cryptography accelerator*/
        uint32_t crc32 :1;    /*  bit7 CRC32   */
        uint32_t res :24;     /*  bit 32:8 res */
    };
}PowerClockRegAhbSet_t;


#ifdef __cplusplus
}
#endif

#endif // CLOCK_REGISTER_TYPES_H
