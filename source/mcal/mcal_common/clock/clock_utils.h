#ifndef CLOCK_GENERAL_UTILS_H
#define CLOCK_GENERAL_UTILS_H

#define HZ_2_KHZ(HZ) ((float)(HZ)/1000.0f)
#define HZ_2_MHZ(HZ) ((float)(HZ)/1000000.0f)
#define GHZ_TO_HZ(HZ) ( (uint64_t) (  ( (float)(HZ) )*1000000000.0f  ) )
#define KHZ_2_HZ(HZ) ((uint32_t) (((float)(HZ))*1000.0f) )
#define MHZ_2_HZ(HZ) ((uint32_t) (((float)(HZ))*1000000.0f) )
#define SEC_TO_TIMER_PERIOD(SEC_S, TIMER_CLOCK_HZ)    (    (  (float)(SEC_S)  ) * (  (float)(TIMER_CLOCK_HZ)  )    )

#endif /* CLOCK_GENERAL_UTILS_H */
