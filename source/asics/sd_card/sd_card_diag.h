#ifndef SD_CARD_DIAG_H
#define SD_CARD_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "sd_card_types.h"

#ifndef HAS_SD_CARD
#error "+HAS_SD_CARD"
#endif

#ifndef HAS_SD_CARD_DIAG
#error "+HAS_SD_CARD_DIAG"
#endif

bool sd_parse_csr(CSR_t* pCSR);
bool sd_parse_scr(SCR_t* pSCR);
bool sd_parse_csd(CSD_t* pCSD);
bool sd_parse_cid(CID_t* pCID);
bool sd_parse_ocr(OCR_t* pOCR);
bool sd_parse_ssr(SSR_t* pSSR);
bool sd_card_diag(SdCardHandle_t* Node);
bool sd_parse_r1(uint8_t byte);
bool sd_parse_r2(uint16_t word);
bool sd_parse_r3(R3_t* R3);
bool sd_parse_r7(R7_t* R7);
char* Mdt2Str(uint16_t mdt);
const char* SdMonth2Str(SdMonth_t month);
const char* Cmd2Str(uint8_t cmd);
void parse_write_flag(uint8_t flags);

#endif /* SD_CARD_DIAG_H */
