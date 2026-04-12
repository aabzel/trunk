#ifndef SYSTICK_MCAL_DEPEN_H
#define SYSTICK_MCAL_DEPEN_H

#ifndef HAS_SYSTICK
#error "+HAS_SYSTICK"
#endif

#ifndef HAS_ARM
#error "+HAS_ARM"
#endif

#ifndef HAS_NVIC
#warning "+HAS_NVIC"
#endif

#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_CORTEX_M
#error  "+HAS_CORTEX_M"
#endif


#endif /* SYSTICK_MCAL_DEPEN_H*/
