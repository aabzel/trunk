#ifndef END_OF_BLOCK_H
#define END_OF_BLOCK_H

#include <stdbool.h>

#include "end_of_block_config.h"
#include "end_of_block_diag.h"
#include "end_of_block_types.h"

bool end_of_block_mcal_init(void);
bool end_of_block_check(const char *const file_name_c,uint32_t lines );

#endif /* END_OF_BLOCK_H */
