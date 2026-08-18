#ifndef NAU8814_ADC_DIAG_H
#define NAU8814_ADC_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "nau8814_adc_const.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_NAU8814
#error "+HAS_NAU8814"
#endif /*HAS_NAU8814*/

#ifndef HAS_NAU8814_DIAG
#error "+HAS_NAU8814_DIAG"
#endif /*HAS_DIAG_NAU8814*/

#ifndef HAS_NAU8814_ADC_DIAG
#error "+HAS_NAU8814_ADC_DIAG"
#endif /*HAS_NAU8814_ADC_DIAG*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool nau8814_adc_diag(uint8_t num);


#endif /* NAU8814_ADC_DIAG_H  */
