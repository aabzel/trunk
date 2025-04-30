#ifndef CALIBRATION_DATA_DEP_H
#define CALIBRATION_DATA_DEP_H

#ifndef HAS_CALIBRATION_DATA
#error "+HAS_CALIBRATION_DATA"
#endif

#ifndef HAS_PARAM
#warning "+HAS_PARAM"
#endif


#ifndef HAS_CRC8
#error "+HAS_CRC8"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

#ifndef HAS_AT24CXX
#error "+HAS_AT24CXX"
#endif


#endif /* CALIBRATION_DATA_DEP_H */
