#ifndef MAX9860_DEP_H
#define MAX9860_DEP_H

#ifndef HAS_MCU
#error "MAX9860 Needs HAS_MCU"
#endif

#ifndef HAS_I2C
#error "MAX9860 Needs HAS_I2C"
#endif

#ifndef HAS_I2S
#warning "MAX9860 Needs HAS_I2S"
#endif

#ifndef HAS_MAX9860
#error "+HAS_MAX9860"
#endif

#ifndef HAS_MULTIMEDIA
#error "MAX9860 Needs HAS_MULTIMEDIA"
#endif

#endif /* MAX9860_DEP_H */
