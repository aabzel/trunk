#ifndef CORRELATOR_S16_CONFIG_H
#define CORRELATOR_S16_CONFIG_H

#include "std_includes.h"
#include "correlator_s16_types.h"

typedef enum {
    CORRELATOR_S16_MUN_CHIRP_CORRELATION ,
    CORRELATOR_S16_MUN_CNT,
}CorrelatorS16LegalNums_t;

extern const CorrelatorS16Config_t CorrelatorS16Config[];
extern CorrelatorS16Handle_t CorrelatorS16Instance[];

uint32_t correlator_s16_get_cnt(void);

#endif /* CORRELATOR_S16_CONFIG_H */
