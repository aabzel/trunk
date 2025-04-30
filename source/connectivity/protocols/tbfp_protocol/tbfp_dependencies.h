#ifndef TBFP_DEPENDENCIES_H
#define TBFP_DEPENDENCIES_H

/*TBFP Trivial Binary Frame Protocol*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_TBFP
#error "+HAS_TBFP"
#endif

#ifndef HAS_CRC
#warning "+HAS_CRC"
#endif

#ifndef HAS_CRC8
#warning "+HAS_CRC8"
#endif

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif

#ifndef HAS_PROTOCOLS
#error "+HAS_PROTOCOLS"
#endif

#ifdef __cplusplus
}
#endif

#endif /* TBFP_DEPENDENCIES_H */
