#ifndef CLOCK_GENERAL_UTILS_H
#define CLOCK_GENERAL_UTILS_H

#define HZ_2_KHZ(HZ) ((double)(HZ)/1000.0)
#define HZ_2_MHZ(HZ) ((double)(HZ)/1000000.0)
#define GHZ_TO_HZ(HZ) ( (uint64_t) (  ( (double)(HZ) )*1000000000.0  ) )
#define KHZ_2_HZ(HZ) ((uint32_t) (((double)(HZ))*1000.0) )
#define MHZ_2_HZ(HZ) ((uint32_t) (((double)(HZ))*1000000.0) )
#define SEC_TO_TIMER_PERIOD(SEC_S,TIMER_CLOCK_HZ)    (((double)(SEC_S)) * ((double)(TIMER_CLOCK_HZ)))

#endif /* CLOCK_GENERAL_UTILS_H */
