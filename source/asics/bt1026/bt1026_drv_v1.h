
#ifndef BT1026_DRV_H
#define BT1026_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "bt1026_config.h"
#include "bt1026_types.h"

bool bt1026_parse_line(char* line, uint32_t size);
bool bt1026_set_volume(uint8_t volume);
bool bt1026_set_volume_id(uint8_t link_id, uint8_t volume);
bool bt1026_get_volume_id(uint8_t link_id, uint8_t* volume);
bool bt1026_get_volume(uint8_t* volume);
bool bt1026_parse_volume(char* line, uint32_t size, Bt1026Handle_t* Bt1026Handle);
bool bt1026_init(void);
bool bt1026_send(uint8_t* array, uint32_t len);
bool bt1026_send_get(uint8_t* array, uint32_t len);
bool bt1026_send_set(uint8_t* param, uint32_t param_len, uint8_t* value, uint32_t val_len);
bool bt1026_proc(void);
bool bt1026_hw_reset(void);
bool bt1026_save(void);
bool bt1026_config_audio(void);
bool bt1026_config_audio_digital(void);

#endif /* BT1026_DRV_H */
