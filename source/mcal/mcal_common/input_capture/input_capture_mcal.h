#ifndef INPUT_CAPTURE_MCAL_API_H
#define INPUT_CAPTURE_MCAL_API_H

#include <stdbool.h>
#include <stdint.h>

#include "input_capture_types.h"
#include "input_capture_config.h"
#ifdef HAS_INPUT_CAPTURE_DIAG
#include "input_capture_diag.h"
#endif

/*API*/
const InputCaptureConfig_t* InputCaptureGetConfig(uint8_t num);
InputCaptureHandle_t* InputCaptureGetNode(uint8_t num);
bool input_capture_init_custom(void);
bool input_capture_mcal_init(void);
bool input_capture_init_cache(const InputCaptureConfig_t* const Config, InputCaptureHandle_t* const Node);
bool input_capture_init_one(uint8_t num);

InputCaptureMode_t InputCaptureOnOffToMode(bool on_off) ;
/*Setters*/
bool input_capture_stop(uint8_t num) ;
bool input_capture_start(uint8_t num);
bool input_capture_channel_ctrl_ll(InputCaptureHandle_t* Node , bool on_off);
bool input_capture_ctrl_ll(InputCaptureHandle_t* Node, bool on_off);
bool input_capture_ctrl(uint8_t num, bool on) ;
bool input_capture_reset(uint8_t num) ;
bool input_capture_channel_ctrl(uint8_t num, bool on_off);

/*Getters*/
bool input_capture_is_valid_duty_cycle(double duty_cycle) ;
bool input_capture_is_valid_channel(InputCaptureChannel_t channel) ;
bool input_capture_counter_get(uint8_t num, uint32_t* const counter);
bool input_capture_pad_get(uint8_t num, Pad_t* const pad);

#endif /* INPUT_CAPTURE_MCAL_API_H */
