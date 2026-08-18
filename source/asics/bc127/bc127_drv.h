
#ifndef BC127_DRV_H
#define BC127_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "bc127_types.h"

bool bc127_set_volume(uint8_t volume);
bool bc127_set_volume_id(uint8_t link_id, uint8_t volume);
bool bc127_get_volume_id(uint8_t link_id, uint8_t* volume);
bool bc127_get_volume(uint8_t* volume);
bool bc127_parse_volume(char* line, uint32_t size, Bc127Handle_t* Bc127Handle);
bool bc127_init(void);
bool bc127_send(uint8_t* array, uint32_t len);
bool bc127_send_get(uint8_t* array, uint32_t len);
bool bc127_send_set(uint8_t* param, uint32_t param_len, uint8_t* value, uint32_t val_len);
bool bc127_proc(void);
bool bc127_check(void);
bool bc127_reset(void);
bool bc127_save(void);
bool bc127_config_audio(void);
bool bc127_config_audio_digital(void);

#endif /* BC127_DRV_H */
