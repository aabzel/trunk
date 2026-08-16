#ifndef MANCHESTER_DECODE_MCAL_H
#define MANCHESTER_DECODE_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "manchester_decode_config.h"
#include "manchester_decode_types.h"

#ifdef HAS_MANCHESTER_DECODE_DIAG
#include "manchester_decode_diag.h"
#endif

/* API */
ManchesterDecodeHandle_t* ManchesterDecodeGetNode(uint8_t num);
const ManchesterDecodeConfig_t* ManchesterDecodeGetConfig(uint8_t num);
bool ManchesterDecodeIsValidConfig(const ManchesterDecodeConfig_t* const Config);

bool manchester_decode_mcal_init(void);
bool manchester_decode_init_custom(void);
bool manchester_decode_init_common(const ManchesterDecodeConfig_t* const Config, ManchesterDecodeHandle_t* const Node);
bool manchester_decode_init_node(ManchesterDecodeHandle_t* const Node);
bool manchester_decode_init_one(uint8_t num);

/*setters*/
bool manchester_decode_proc_sample(const uint8_t num, const uint8_t in, uint8_t * const out);

/*getters*/
bool manchester_decode_array(uint8_t num,
                             const uint8_t* const EncodedData,
                             const uint32_t encoded_data_size,
                             uint8_t* const DecodedData,
                             const uint32_t decoded_data_size);

uint8_t manchester_decode_out_to_val(const ManchesterDecodeAction_t out);

#ifdef __cplusplus
}
#endif

#endif /* MANCHESTER_DECODE_MCAL_H */
