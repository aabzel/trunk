#ifndef DECAWAVE_DEPENDENCIES_H
#define DECAWAVE_DEPENDENCIES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DECAWAVE
#error "+HAS_DECAWAVE"
#endif

#ifndef HAS_CRC
#error "+HAS_CRC"
#endif

#ifndef HAS_UWB
#error "+HAS_UWB"
#endif

#ifndef HAS_CRC16
#error "+HAS_CRC16"
#endif

#ifndef HAS_DS_TWR
#warning "+HAS_DS_TWR"
#endif

#ifndef HAS_PROTOCOLS
#error "+HAS_PROTOCOLS"
#endif

#ifndef HAS_PARAM
#warning "+HAS_PARAM"
#endif

#ifndef HAS_TBFP
#error "+HAS_TBFP"
#endif

#ifdef __cplusplus
}
#endif

#endif /* DECAWAVE_DEPENDENCIES_H */
