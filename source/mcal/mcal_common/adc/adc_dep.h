#ifndef ADC_DEP_H
#define ADC_DEP_H

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#ifndef HAS_ADC
#error "+ HAS_ADC"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_SENSITIVITY
#error "+ HAS_SENSITIVITY"
#endif

#endif /* ADC_DEP_H  */
