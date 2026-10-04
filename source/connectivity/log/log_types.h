#ifndef LOG_TYPES_H
#define LOG_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "log_constants.h"

#ifdef HAS_INTERFACES
#include "interfaces_types.h"
#endif

#ifdef HAS_SYSTEM
#include "sys_constants.h"
#endif

#ifdef HAS_INTERFACES
#include "interfaces_types.h"
// keyword "interface" is reserved in Win PC builds
#define LOG_IF_COMMON_VARIABLES InterfaceType_t inter_face;
#else
#define LOG_IF_COMMON_VARIABLES
#endif

typedef union {
    uint16_t word;
    struct{
        uint16_t protected :1;
        uint16_t trace :1;     //coverage
        uint16_t paranoid :1;
        uint16_t debug :1;
        uint16_t notice :1;
        uint16_t info :1;
        uint16_t warning :1;
        uint16_t error :1;
        uint16_t critical :1;
        uint16_t res :7;
    };
}LogLevels_t;

#define LOG_COMMON_VARIABLES   \
    LOG_IF_COMMON_VARIABLES    \
    bool in_place;             \
    bool valid;                \
    bool colored;              \
    bool time_stamp;           \
    uint8_t num;

typedef struct {
    LOG_COMMON_VARIABLES
}LogConfig_t;

typedef struct {
    LOG_COMMON_VARIABLES
    uint32_t serial_nun;
}LogHandle_t;

typedef struct {
    LOG_COMMON_VARIABLES
    LogLevels_t levels[ALL_FACILITY];
    bool flush;
    bool new_line;
    uint32_t serial_nun;
#ifdef HAS_LOG_DIAG
    bool facility_name;
#endif /**/


    uint32_t up_time_prev_ms;
}Log_t;


#ifdef __cplusplus
}
#endif

#endif /* LOG_TYPES_H */
