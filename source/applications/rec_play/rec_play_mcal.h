#ifndef REC_PLAY_MCAL_H
#define REC_PLAY_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "rec_play_config.h"
#include "rec_play_types.h"

#ifdef HAS_REC_PLAY_DIAG
#include "rec_play_diag.h"
#endif

/* API */
RecPlayHandle_t* RecPlayGetNode(uint8_t num);
const RecPlayConfig_t* RecPlayGetConfig(uint8_t num);
bool RecPlayIsValidConfig(const RecPlayConfig_t* const Config);

#ifdef HAS_REC_PLAY_CUSTOM
const RecPlayInfo_t* RecPlayGetInfo(uint8_t num);
#endif

bool rec_play_mcal_init(void);
bool rec_play_init_custom(void);
bool rec_play_init_common(const RecPlayConfig_t* const Config, RecPlayHandle_t* const Node);
bool rec_play_init_node(RecPlayHandle_t* const Node);
bool rec_play_init_one(uint8_t num);

bool rec_play_proc_one(uint8_t num);
bool rec_play_proc(void);

/*setters*/
bool rec_play_start_test(uint8_t num, float duration_s);
bool rec_play_start(uint8_t num, char* file_name, float duration_s);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* REC_PLAY_MCAL_H */
