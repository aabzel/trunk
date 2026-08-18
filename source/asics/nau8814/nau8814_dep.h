#ifndef NAU8814_DEP_H
#define NAU8814_DEP_H

#ifndef HAS_MICROCONTROLLER
#error "NAU8814 Needs HAS_MICROCONTROLLER"
#endif

#ifndef HAS_GPIO
#error "NAU8814 Needs HAS_GPIO"
#endif

#ifndef HAS_I2C
#error "NAU8814 Needs HAS_I2C"
#endif

#ifndef HAS_I2S
#warning "NAU8814 Needs HAS_I2S"
#endif

#ifndef HAS_PWM
#warning "NAU8814 Needs HAS_PWM"
#endif

#ifndef HAS_NAU8814
#error "+HAS_NAU8814"
#endif

#ifndef HAS_STORAGE
#error "NAU8814 Needs HAS_STORAGE"
#endif


#endif /* NAU8814_DEP_H */
