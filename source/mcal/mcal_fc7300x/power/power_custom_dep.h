#ifndef POWER_CUSTOM_DEP_H
#define POWER_CUSTOM_DEP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MCU
#error "+HAS_MCU"
#endif /*HAS_MCU*/

#ifndef HAS_POWER
#error "+HAS_POWER"
#endif /*HAS_POWER*/

#ifndef HAS_POWER_ISR
#error "+HAS_POWER_ISR"
#endif /*HAS_POWER_ISR*/


#ifdef __cplusplus
}
#endif

#endif /* POWER_CUSTOM_DEP_H */
