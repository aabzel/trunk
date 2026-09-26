#ifndef EXT_INT_CUSTOM_DEP_H
#define EXT_INT_CUSTOM_DEP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MCU
#error "+HAS_MCU"
#endif /*HAS_MCU*/

#ifndef HAS_EXT_INT
#error "+HAS_EXT_INT"
#endif /*HAS_EXT_INT*/

#ifndef HAS_EXT_INT_ISR
#error "+HAS_EXT_INT_ISR"
#endif /*HAS_EXT_INT_ISR*/


#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_CUSTOM_DEP_H */
