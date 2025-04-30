#ifndef STARAGE_H
#define STARAGE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "storage_types.h"
#include "storage_diag.h"

bool storage_proc_cmd(uint8_t tbfp_num, const uint8_t* const payload, const uint32_t size);


#ifdef __cplusplus
}
#endif

#endif /* STARAGE_H */
