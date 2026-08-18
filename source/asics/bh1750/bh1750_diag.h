#ifndef BH1750_DIAG_H
#define BH1750_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "bh1750_types.h"

#ifndef HAS_BH1750
#error "+HAS_BH1750"
#endif

bool bh1750_diag(char* key_word1, char* key_word2);

#endif /* BH1750_DIAG_H  */
