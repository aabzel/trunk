#ifndef SPIFI_CUSTOM_DEP_H
#define SPIFI_CUSTOM_DEP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#ifndef HAS_SPIFI
#error "+HAS_SPIFI"
#endif /*HAS_SPIFI*/

#ifndef HAS_SPIFI_ISR
#error "+HAS_SPIFI_ISR"
#endif /*HAS_SPIFI_ISR*/


#ifdef __cplusplus
}
#endif

#endif /* SPIFI_CUSTOM_DEP_H */
