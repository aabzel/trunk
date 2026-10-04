#ifndef ISO_TP_BOARD_H
#define ISO_TP_BOARD_H

#include "iso_tp_types.h"

extern const IsoTpConfig_t IsoTpConfig[];
extern IsoTpHandle_t IsoTpInstance[];

uint32_t iso_tp_get_cnt(void);

#endif /*ISO_TP_BOARD_H*/
