#ifndef W25Q32JV_DEP_H
#define W25Q32JV_DEP_H

#ifndef HAS_GPIO
#warning "W25Q32JV Needs HAS_GPIO"
#endif

#ifndef HAS_MICROCONTROLLER
#error "W25Q32JV Needs HAS_MCU"
#endif

#ifndef HAS_STORAGE
#warning "W25Q32JV Needs HAS_STORAGE"
#endif

#ifndef HAS_W25Q32JV
#error "+HAS_W25Q32JV"
#endif

#ifndef HAS_TIME
#warning "+HAS_TIME"
#endif

#endif /* W25Q32JV_DEP_H */
