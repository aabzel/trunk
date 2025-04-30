#include "shared_array.h"

/* Diagnostic common array
 * One single static array for all Software components.
 * It is done to save RAM memory
 * */
char text[SHARED_ARRAY_SIZE] = {0};
