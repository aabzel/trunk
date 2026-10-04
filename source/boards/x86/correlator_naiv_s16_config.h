#ifndef CORRELATOR_NAIV_S16_CONFIG_H
#define CORRELATOR_NAIV_S16_CONFIG_H

#include "std_includes.h"
#include "correlator_naiv_s16_types.h"

typedef enum {
    CORRELATOR_NAIV_S16_MUN_CHIRP_CORRELATION ,
    CORRELATOR_NAIV_S16_MUN_M_SEC,
    CORRELATOR_NAIV_S16_MUN_CNT,
}CorrelatorNaivS16LegalNums_t;

extern const CorrelatorNaivS16Config_t CorrelatorNaivS16Config[];
extern CorrelatorNaivS16Handle_t CorrelatorNaivS16Instance[];

uint32_t correlator_naiv_s16_get_cnt(void);

#endif /* CORRELATOR_NAIV_S16_CONFIG_H */
