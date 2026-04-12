#ifndef QWORD_MISC_H
#define QWORD_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "data_types.h"

uint64_t unsigned_big_endian_to_u64(const uint8_t* const memory, const uint32_t param_size) ;
uint64_t max64u(uint64_t max64u_x1, uint64_t max64u_x2);
uint64_t min64u(uint64_t min64u_x1, uint64_t min64u_x2) ;
uint64_t reverse_byte_order_uint64(const uint64_t in4byteVal);

bool data_u64_init(U64Value_t* const Node);
bool data_u64_update(U64Value_t* const Node, uint64_t val) ;
bool fetch_big_endian_qword(const uint8_t* const data,
                            const uint32_t size,
                            uint64_t* const qword);

#ifdef __cplusplus
}
#endif

#endif /* QWORD_MISC_H */
