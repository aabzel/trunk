#ifndef LOAD_DETECT_DEP_H
#define LOAD_DETECT_DEP_H

#ifndef HAS_MCU
#error "+ HAS_MCU"
#endif

#ifndef HAS_TIME
#error "+ HAS_TIME"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_LOAD_DETECT
#error "+ HAS_LOAD_DETECT"
#endif

#endif /* LOAD_DETECT_DEP_H  */
