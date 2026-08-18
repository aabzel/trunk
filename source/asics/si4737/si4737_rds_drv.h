#ifndef SI4737_RDS_DRV_H
#define SI4737_RDS_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "si4737_types.h"

#ifndef HAS_RDS
#error "+HAS_RDS"
#endif

#ifndef HAS_SI4737
#error "SI4737 Needs HAS_SI4737"
#endif

bool si4737_init_rds(void);
bool si4737_set_fm_rds_int_source(void);
bool si4737_get_fm_rds_int_fifo_cnt(uint8_t* rds_fifo_cnt);
bool si4737_get_fm_rds_status(Si4737Handler_t* instance, uint8_t *rds_fifo_cnt);
bool si4737_set_fm_rds_config(bool rds_en);
bool si4737_set_fm_rds_int_fifo_cnt(uint8_t rds_fifo_cnt);


#endif /* SI4737_RDS_DRV_H */
