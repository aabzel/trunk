#ifndef UDS_PROTOCOL_H
#define UDS_PROTOCOL_H

/*UDS Trivial Binary Frame Protocol
 * Spec: ISO 14229-1
 * */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "system.h"
#include "uds_config.h"
#include "uds_diag.h"
#include "uds_types.h"

const RoutineIdentifierConfig_t* RoutineIdentifierGetConfig(UdsRoutineIdentifier_t routine_identifier);

UdsHandle_t* UdsGetNode(uint8_t num);
const UdsConfig_t* UdsGetConfig(uint8_t num);

DidHandle_t* DidGetNode(uint8_t num);
const DidConfig_t* DidGetConfig(uint8_t num);

DidHandle_t* DidGetNodeByDid(UdsDid_t did);
const DidConfig_t* DidGetConfigByDid(UdsDid_t did);

UdsHandle_t* UdsIfToNode(Interfaces_t interface);

bool uds_start_routine(UdsRoutineIdentifier_t routine_identifier);
bool uds_send(uint8_t num, const uint8_t* const data, size_t size);
bool uds_proc_rx_data(uint8_t num, const uint8_t* const data, size_t size);
bool uds_read_data_by_identifier(uint8_t num, uint16_t did);
bool uds_check(void);
bool uds_init_one(uint8_t num);
bool uds_proc_one(uint8_t num);
bool uds_mcal_init(void);
bool uds_proc(void);

bool did_mcal_init(void);
bool did_init_one(uint8_t num);
bool did_proc(void);
bool did_proc_one(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* UDS_PROTOCOL_H */
