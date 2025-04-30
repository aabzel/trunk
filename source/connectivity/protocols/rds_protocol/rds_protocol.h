#ifndef RDS_PROTOCOL_H
#define RDS_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "rds_constants.h"
#include "rds_types.h"

#ifndef HAS_RDS_DIAG
#include "rds_diag.h"
#endif


#ifndef HAS_FM_TUNER
#error "+HAS_FM_TUNER"
#endif

#ifndef HAS_RDS
#error "+HAS_RDS"
#endif

extern RdsProtocol_t RdsProtocol;

int8_t RdsLocTimeOffSet2Num(uint8_t loctimeoffset);
bool rds_protocol_init(void);
bool rds_proc_message(uint16_t* word);
bool rds_mirror_words(uint16_t* word);
bool rds_reverse_words(uint16_t* word);

#ifdef __cplusplus
}
#endif

#endif /* RDS_PROTOCOL_H */
