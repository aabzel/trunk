#ifndef W25Q16BV_DEP_H
#define W25Q16BV_DEP_H

#ifndef HAS_GPIO
#error "W25Q16BV Needs HAS_GPIO"
#endif

#ifndef HAS_MCU
#error "W25Q16BV Needs HAS_MCU"
#endif

#ifndef HAS_SPI
#error "W25Q16BV Needs HAS_SPI"
#endif

#ifndef HAS_STORAGE
#error "W25Q16BV Needs HAS_STORAGE"
#endif

#ifndef HAS_W25Q16BV
#error "+HAS_W25Q16BV"
#endif

#ifndef HAS_TIME
#error "+HAS_TIME"
#endif

#endif /* W25Q16BV_DEP_H */
