#ifndef LIS3DH_DEP_H
#define LIS3DH_DEP_H

#ifndef HAS_GPIO
#error "LIS3DH Needs HAS_GPIO"
#endif

#ifndef HAS_I2C
#warning "LIS3DH Needs HAS_I2C"
#endif


#ifndef HAS_SPI
#warning "LIS3DH Needs HAS_SPI"
#endif

#ifndef HAS_VECTOR
#error "LIS3DH Needs HAS_VECTOR"
#endif

#ifndef HAS_LIS3DH
#error "+HAS_LIS3DH"
#endif

#ifndef HAS_MICROCONTROLLER
#error "LIS3DH Needs HAS_MICROCONTROLLER"
#endif

#endif /* LIS3DH_DEP_H */
