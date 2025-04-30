#ifndef BUTTON_DEP_H
#define BUTTON_DEP_H

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_BUTTON
#error "+ HAS_BUTTON"
#endif

#ifndef HAS_FLASH
#error "+ HAS_FLASH"
#endif

#ifndef HAS_TIME
#warning "+ HAS_TIME"
#endif

#endif /* BUTTON_DEP_H  */
