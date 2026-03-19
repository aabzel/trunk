#ifndef TRNG_MCAL_H
#define TRNG_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "trng_config.h"
#include "trng_types.h"
#ifdef HAS_TRNG_DIAG
#include "trng_diag.h"
#endif

/* API */
tRngHandle_t* tRngGetNode(uint8_t num);
const tRngConfig_t* tRngGetConfig(uint8_t num);
bool tRngIsValidConfig(const tRngConfig_t* const Config);

bool trng_mcal_init(void);
bool trng_init_custom(void);
bool trng_init_common(const tRngConfig_t* const Config, tRngHandle_t* const Node);
bool trng_init_one(uint8_t num);
bool trng_init_node(tRngHandle_t* const Node) ;

bool trng_proc_one(uint8_t num);
bool trng_proc(void);

/*setters*/

/*getters*/
uint32_t trng_static_get_rand(void);
bool trng_get_qword(uint64_t* const qword);
bool trng_get_dword(uint32_t* const dword);
bool trng_get_s32(int32_t* const sdword);
bool trng_get_word(uint16_t* const word);
bool trng_get_byte(uint8_t* const byte);


#ifdef __cplusplus
}
#endif

#endif /* TRNG_MCAL_H */
