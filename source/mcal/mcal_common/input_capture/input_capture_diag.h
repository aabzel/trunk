#ifndef INPUT_CAPTURE_DIAG_H
#define INPUT_CAPTURE_DIAG_H

#include <stdbool.h>

#include "input_capture_types.h"

const char* InputCaptureConfigToStr(const InputCaptureConfig_t* const Config);

bool InputCaptureDiagConfig(const InputCaptureConfig_t* const Config);
bool input_capture_diag(char* key_word1, char* key_word2);

#endif /* INPUT_CAPTURE_DIAG_H */
