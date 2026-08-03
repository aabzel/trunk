#ifndef CORRELATOR_S16_TYPES_H
#define CORRELATOR_S16_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "correlator_s16_const.h"
#include "circular_buffer_types.h"


/*CorrelatorS16 sample can be wery bin in case of CORRELATOR_S16_MODE_CORRELATION mode
 *  int32_t can overflow*/

#define CORRELATOR_S16_COMMON_VARIABLE       \
    char* name;                              \
    float sample_rate_hz;                    \
    char* file_name_out;                     \
    char* file_name_in ;                     \
    uint32_t num;                            \
    uint32_t size;    /*config Order M*/     \
    uint32_t max_size;    /*max Order M*/    \
    int16_t* ReferenceSignal;     /*Array of default coefficients h[i]*/   \
    int16_t* x;    /*Array of memory*/      \
    bool valid;                \

typedef struct {
    CORRELATOR_S16_COMMON_VARIABLE
    /*Array of coefficients*/
} CorrelatorS16Config_t;

typedef struct {
    CORRELATOR_S16_COMMON_VARIABLE
    bool init;
    CircularBufferIndexInfo_t indexer;
    uint32_t proc_cnt;
    /*Array of values*/
} CorrelatorS16Handle_t;

#ifdef __cplusplus
}
#endif

#endif /* CORRELATOR_S16_TYPES_H */
