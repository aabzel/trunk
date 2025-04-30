#ifndef PDM_DRV_H
#define PDM_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "pdm_config.h"
#include "pdm_types.h"

bool pdm_init(void);
bool pdm_proc(void);
bool pdm_init_one(uint8_t num);
bool pdm_listen(uint8_t num, uint32_t duration_ms);
bool pdm_proc_one(uint8_t num);
bool pdm_calc_dft(uint8_t num);
bool PdmIsValidConfig(const PdmConfig_t* const Config);
bool pdm_buf_set(uint8_t num, const int16_t* const buf, uint16_t len);
bool pdm_ctrl(uint8_t num, bool on_off, MicMode_t mode);
bool pdm_calc_dft_ll(PdmHandle_t* const Node);
const PdmConfig_t* PdmGetConfig(uint8_t num);
PdmStaticInfo_t* PdmGetStaticNode(uint8_t num);
PdmHandle_t* PdmGetNode(uint8_t num);

#endif /* PDM_DRV_H */
