#ifndef BASICAL_MACRO_UTIL_H
#define BASICAL_MACRO_UTIL_H

#define K_BYTES 1024UL
#define M_BYTES (1024UL*K_BYTES)


/*

   #include "macro_utils.h"

 */
//#define GBYTE_BYTE(GBYTE) ((GBYTE)*1024UL*1024UL*1024UL)

#define KBYTE_BYTE(KBYTE) ((KBYTE)*1024UL)
#define MBYTE_BYTE(MBYTE) KBYTE_BYTE((MBYTE)*1024UL)
#define GBYTE_BYTE(GBYTE) MBYTE_BYTE(1024UL*(GBYTE))

#define BYTES_2_KBYTES(BYTES) (((float)(BYTES))/(1024.0))
#define BYTES_2_KBYTES_U(BYTES) ((BYTES)/1024)

#define MHZ_TO_HZ_U(MHZ) ((MHZ)*1000000U)
#define INT_TO_FLOAT(REAL_NUMBER)  (   (float)(REAL_NUMBER)   )
#define MBPS_TO_BPS(MBPS) (   (uint32_t)    ( INT_TO_FLOAT(MBPS)   *1000000.0   ) )
#define KBPS_TO_BPS(MBPS) (   (uint32_t)    ( INT_TO_FLOAT(MBPS)   *1000.0   ) )

#ifdef HAS_NORTOS
#define IS_ENABLED(x) x
#endif /*HAS_NORTOS*/

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define SECTION_NVRAM __attribute__((section (".NvRam")))

#ifdef HAS_CFG_DATA_SECTION
#define SECTION_CFG_DATA __attribute__((section (".ConfigurationData")))
#else
#define SECTION_CFG_DATA
#endif

#endif /* BASICAL_MACRO_UTIL_H */
