#ifndef SET_CONST_H
#define SET_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SET
#error "+HAS_SET"
#endif

#ifndef HAS_ADT
#error "+HAS_ADT"
#endif

#ifndef HAS_CRC32
#error "+HAS_CRC32"
#endif

#ifndef HAS_CRC
#error "+HAS_CRC"
#endif

#ifndef HAS_SW_NVRAM
#error "+HAS_SW_NVRAM"
#endif

#define SET_PREAMBLE 0x5354

#ifdef __cplusplus
}
#endif

#endif /* SET_CONST_H */
