#ifndef LOG_TYPES_H
#define LOG_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif

#ifdef HAS_INTERFACES
#include "interfaces_const.h"
#endif

#include "log_constants.h"
#ifdef HAS_SYSTEM
#include "sys_constants.h"
#endif

#ifdef HAS_INTERFACES
#include "interfaces_const.h"
// keyword "interface" is reserved in Win PC builds
#define LOG_IF_COMMON_VARIABLES Interfaces_t interface_;
#else
#define LOG_IF_COMMON_VARIABLES
#endif

#define LOG_COMMON_VARIABLES   \
    LOG_IF_COMMON_VARIABLES    \
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
    log_level_t levels[ALL_FACILITY];
    bool flush;
    bool new_line;
    uint32_t serial_nun;
#ifdef HAS_LOG_DIAG
    bool facility_name;
#endif /*HAS_LOG_DIAG*/

#ifdef HAS_LOG_TIME_STAMP
    bool time_stamp;
#endif/*HAS_LOG_TIME_STAMP*/

#ifdef HAS_LOG_COLOR
    bool colored;
#endif/*HAS_LOG_COLOR*/
    uint64_t up_time_ms;
}Log_t;


#ifdef __cplusplus
}
#endif

#endif /* LOG_TYPES_H */
