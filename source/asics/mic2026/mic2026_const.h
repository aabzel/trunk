
#ifndef MIC2026_CONST_H
#define MIC2026_CONST_H

#include "time_mcal.h"

#define CHAN_NAME_SIZE 15
#define MIC2026_CHAN_CNT 2

#ifndef HAS_MIC2026
#error "+HAS_MIC2026"
#endif

typedef enum {
   CHANNEL_A=1,
   CHANNEL_B=2,
   CHANNEL_UNDEF=3,
}Mic2026Channel_t;

#define MIC2026_PERIOD_US MSEC_2_USEC(500)


#endif /* MIC2026_CONST_H */
