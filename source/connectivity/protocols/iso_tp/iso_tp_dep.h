#ifndef ISO_TP_DEPENDENCIES_H
#define ISO_TP_DEPENDENCIES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_ISO_TP
#error "+HAS_ISO_TP"
#endif

#ifndef HAS_TIME
#error "+HAS_TIME"
#endif

#ifndef HAS_PROTOCOLS
#error "+HAS_PROTOCOLS"
#endif

#ifndef HAS_CAN
#warning "+HAS_CAN"
#endif

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_DEPENDENCIES_H */
