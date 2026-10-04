#ifndef SD_CARD_DIAG_H
#define SD_CARD_DIAG_H

#include "std_includes.h"
#include "sd_card_types.h"

#ifndef HAS_SD_CARD
#error "+HAS_SD_CARD"
#endif

#ifndef HAS_SD_CARD_DIAG
#error "+HAS_SD_CARD_DIAG"
#endif

bool sd_parse_sr(const SR_t* const pSR);
bool sd_parse_csr(CSR_t* pCSR);
bool sd_parse_scr(SCR_t* pSCR);
bool sd_parse_csd(CSD_t* pCSD);
bool sd_parse_cid(const CID_t* const pCID);
bool sd_parse_ocr(const OCR_t* const pOCR);
bool sd_parse_ssr(SSR_t* pSSR);
bool sd_card_diag(SdCardHandle_t* Node);
bool sd_parse_r1(const uint8_t byte);
bool sd_parse_r2(uint16_t word);
bool sd_parse_r3(R3_t* R3);
bool sd_parse_r7(R7_t* R7);
char* MdtToStr(uint16_t mdt);
const char* MidToStr(const SdCardManufacturer_t mid) ;
const char* SdCardStatusRegToStr(const SR_t* const Reg);
const char* SdSpiAddrMethodToStr(const SdSpiAddressMethod_t addr_type );
const char* SdMonthToStr(SdMonth_t month);
const char* SdCardRegOcrToStr(const OCR_t* const Reg);
const char* CmdToStr(uint8_t cmd);
void parse_write_flag(uint8_t flags);

#endif /* SD_CARD_DIAG_H */
