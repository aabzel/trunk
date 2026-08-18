#ifndef SI4703_DEP_H
#define SI4703_DEP_H

#ifndef HAS_TIME
#error "+HAS_TIME"
#endif

#ifndef HAS_I2C
#warning "SI4703 Needs HAS_I2C"
#endif

#ifndef HAS_SPI
#warning "SI4703 Needs HAS_SPI"
#endif

#ifndef HAS_GPIO
#error "SI4703 Needs HAS_GPIO"
#endif

#ifndef HAS_SI4703
#error "+HAS_SI4703"
#endif

#endif /* SI4703_DEP_H */

