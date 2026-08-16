#ifndef M_SEQ_TYPES_H
#define M_SEQ_TYPES_H

#include "std_includes.h"
#include "m_seq_const.h"

#define M_SEQ_COMMON_VARIABLES                         \
    char* name;                                        \
    uint8_t* generated_code;                           \
    uint8_t num;                                       \
    uint32_t code_size;                                \
    uint8_t* memory;                                   \
    uint8_t* feedback;                                 \
    uint32_t max_size;                                 \
    uint32_t cur_size;                                 \
    bool valid;

typedef struct {
    M_SEQ_COMMON_VARIABLES
}MseqConfig_t;

typedef struct {
    M_SEQ_COMMON_VARIABLES
    bool init;
    uint32_t m_seq_len; /*len of generated sequense*/
    uint32_t spin;
}MseqHandle_t;


#endif /* M_SEQ_TYPES_H */
