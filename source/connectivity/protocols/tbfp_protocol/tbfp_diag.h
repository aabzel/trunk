#ifndef TBFP_DIAG_H
#define TBFP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "tbfp.h"

bool tbfp_generate_jump(const uint32_t base_address);
bool tbfp_storage_erase_generate(void);
bool tbfp_storage_write_generate(uint32_t address, uint16_t size, uint8_t pattern);
bool tbfp_storage_read_generate(uint8_t num, uint32_t address, uint16_t size);
const char* TbfpPayloadToStr(const TbfpPayloadId_t payload_id,
		                     const uint8_t* const payload );
const char* TbfpPayloadStorageToStr(const uint8_t* const payload );
const char* TbfpHeaderToStr(const TbfpHeader_t* const Header);
const char* TbfpNode2Str(const TbfpHandle_t* const Node);
const char* TbfpPayloadIdToStr(TbfpPayloadId_t id);
const char* TbfpRxState2Str(RxState_t rx_state);
const char* TbfpFlagToStr(TbfpFrameFlags_t flags);
bool tbfp_print_ping_frame(TbfPingFrame_t* pingFrame);
bool tbfp_diag(void);
bool tbfp_rate_diago(void);
bool tbfp_error(void);
bool tbfp_parse_frame(const uint8_t* const data, const uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* TBFP_DIAG_H */
