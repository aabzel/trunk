#ifndef RDS_DIAG_H
#define RDS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "rds_types.h"

bool rds_diag(void) ;
char* CountryCode2Str(uint8_t code);
const char* CovAreaCode2Str(uint8_t code);
const char* MessageGroup2Str(uint8_t id);
const char* ProgramType2Str(uint8_t code);
const char* GroupType2Str(uint8_t code);
bool rds_print_message(RdsMessage_t* RdsMessage);
bool RdsDiagNode(RdsProtocol_t* RdsProtocol);
const char* ClockTimeDate2Str(const ClockTimeDate_t *const Node);

#ifdef __cplusplus
}
#endif

#endif /* RDS_DIAG_H */
