#ifndef H__BITORDER_H
#define H__BITORDER_H

#ifdef MATLAB_MEX_FILE
#define INTEL_ORDER 1
#endif

#ifdef __LITTLE_ENDIAN__
#if __LITTLE_ENDIAN__ == 1
#define INTEL_ORDER 1
#endif
#endif

#ifdef __BIG_ENDIAN__
#if __BIG_ENDIAN__ == 1
#define MOTOROLA_ORDER 1
#endif
#endif

#ifdef __little_endian__
#if __little_endian__ == 1
#define INTEL_ORDER 1
#endif
#endif

#ifdef __big_endian__
#if __big_endian__ == 1
#define MOTOROLA_ORDER 1
#endif
#endif

#if defined(__BYTE_ORDER__)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define INTEL_ORDER 1
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define MOTOROLA_ORDER 1
#endif
#endif

#if defined(__GLIBC__)
#include <endian.h>
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN
#define INTEL_ORDER 1
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN
#define MOTOROLA_ORDER 1
#endif
#endif

#if !(defined(INTEL_ORDER) || defined(MOTOROLA_ORDER))
#error "Unknown bit order"
#endif

#endif /* H__BITORDER_H */
