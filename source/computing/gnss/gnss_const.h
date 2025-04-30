#ifndef GNSS_CONST_H
#define GNSS_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gnss_dep.h"
#include "utils_math.h"
#ifdef HAS_GPS
#include "gps_const.h"
#endif

typedef enum {
    SIGNAL_SIN = 1,
    SIGNAL_COS = 2,

    SIGNAL_UNDEF=0,
}SignalType_t;


#define PRN_TIME_S (0.001)

#define MAX_FREQ_SHIFT_HZ_PER_S (1.0)

#define MAX_FREQ_SHIFT_HZ_PER_PRN (MAX_FREQ_SHIFT_HZ_PER_S/PRN_TIME_S)


#define SPEED_OF_LIGHT_MPS  ((double)299792458.0)
/*
 * FLL_CONST (0.01/180.0)
 * FLL_CONST (0.02/180.0)
 * FLL_CONST (1.0/90.0)
 * #define FLL_CONST (1.0/180.0)
 * #define FLL_CONST (-1.0/180.0)
 */
#define FLL_CONST (1.0/180.0)
//#define PLL_FLL_CONST (-1.0/180.0)
#define PLL_FLL_CONST (1.0/(2.0*180.0))
// (10.0)

#define DEG_TO_DAD_COEF (3.15149/180.0)
//#define TRACKING_PLL1_C1 (0.001)
#define TRACKING_PLL_INTEGRAL_C2 (1.0/45.0) //1/3 1/4 2 1
/*
 * sig const ring
 * TRACKING_PLL1_C2 (2.5)
 * ------------
// TRACKING_PLL1_C2=2  sig const ring
// TRACKING_PLL1_C2=+1 sig const 4 clusters +
// TRACKING_PLL1_C2=+0.1 sig const 4 clusters
// TRACKING_PLL1_C2=-1 sig const ring
// TRACKING_PLL1_C2=0.5 sig const ring
// TRACKING_PLL1_C2=0.01 sig const 4 clusters
// TRACKING_PLL1_C2 (+1.5) sig const ring
TRACKING_PLL1_C2 (4.0)  ring
TRACKING_PLL1_C2 (0.25) sig const 4 clusters x
*/
//#define TRACKING_PLL_INTEGRAL_C2 (TRACKING_PLL_PROP_C1/4.0)
//#define TRACKING_PLL_INTEGRAL_C2 (TRACKING_PLL_PROP_C1/2.0)

#define SCALE 100.0

#define TRACKING_FLL1 (2.0f)

#define NOISE_BANDWIDTH_HZ (60.0)
#define DAMPING_RATIO (1.1)
#define SAMPLING_TIME (PRN_TIME_S)

#define OMEG_NATURAL ((8.0*DAMPING_RATIO*NOISE_BANDWIDTH_HZ)/(4.0*DAMPING_RATIO*NOISE_BANDWIDTH_HZ+1.0))

#define TRACKING_PLL_C_DENOMINATOR  (4.0+4.0*DAMPING_RATIO*OMEG_NATURAL*SAMPLING_TIME+POW_2(OMEG_NATURAL*SAMPLING_TIME))

#define TRACKING_PLL_PROP_C1 SCALE*(  (8.0*DAMPING_RATIO*OMEG_NATURAL*SAMPLING_TIME)    /TRACKING_PLL_C_DENOMINATOR     ) /*1000-orig val*/

#define TRACKING_PLL_DIFF_C2 SCALE*((4.0*POW_2(OMEG_NATURAL*SAMPLING_TIME) )/TRACKING_PLL_C_DENOMINATOR) /*10-orig val*/

#ifdef __cplusplus
}
#endif

#endif /* GNSS_CONST_H */
