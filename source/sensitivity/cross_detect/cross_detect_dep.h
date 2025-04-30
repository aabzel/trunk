#ifndef CROSS_DETECT_DEP_H
#define CROSS_DETECT_DEP_H

#ifndef HAS_MCU
#error "+ HAS_MCU"
#endif

#ifndef HAS_TIME
#error "+ HAS_TIME"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_CROSS_DETECT
#error "+ HAS_CROSS_DETECT"
#endif

#endif /* CROSS_DETECT_DEP_H  */
