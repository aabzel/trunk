#ifndef UDS_TYPES_H
#define UDS_TYPES_H

/*UDS Unified Diagnostic Services */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "data_utils.h"
#include "uds_const.h"
#include "system.h"
#include "protocol_types.h"
#include "storage_types.h"

typedef struct {
    uint8_t buff[3];
    struct {
        uint8_t sid;
        uint16_t did;
    }__attribute__((__packed__));
}__attribute__((__packed__)) UdsReadDataByIdFrame_t;


#define DID_COMMON_VARIABLES         \
    uint8_t num;                     \
    UdsDid_t did; /*DataIdentifier*/ \
    StorageType_t type;              \
    StorageAccess_t access;          \
    size_t size;                     \
    bool nvram;                      \
    char* name;                      \
    bool valid;

typedef struct {
    DID_COMMON_VARIABLES
    char default_value[10];
}DidConfig_t;

typedef struct {
    UdsRoutineIdentifier_t routine_identifier;
    char* name;
    bool valid;
}RoutineIdentifierConfig_t;


typedef struct {
    DID_COMMON_VARIABLES
    uint8_t buff[16];
} DidHandle_t;

#define UDS_COMMON_VARIABLES       \
    bool valid;                    \
    uint32_t num;                  \
    uint8_t iso_tp_num;


typedef struct {
    UDS_COMMON_VARIABLES
    uint8_t expexted_sid;
    uint32_t tx_time_stamp_ms;
    uint32_t rx_wait_ms;
    uint32_t err_cnt;
    UdsState_t state;
    uint16_t routine_identifier;
    uint8_t tx_frame[16];
    size_t tx_size;
} UdsHandle_t;

typedef struct  {
    UDS_COMMON_VARIABLES
}UdsConfig_t;


#ifdef __cplusplus
}
#endif

#endif /* UDS_TYPES_H */
