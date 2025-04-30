#ifndef FLASH_FS_DIAG_H
#define FLASH_FS_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool flash_fs_diag(void);
bool flash_fs_scan(uint32_t start_page_addr, uint32_t page_len, char* key_word1, char* key_word2);

#ifdef __cplusplus
}
#endif

#endif /* FLASH_FS_DIAG_H */
