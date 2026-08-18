
#ifndef AD9833_DRV_H
#define AD9833_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "ad9833_types.h"

bool ad9833_init(void);
bool ad9833_reset(uint8_t num);
bool ad9833_write(uint8_t num, uint16_t word);
bool ad9833_set_signal(uint8_t num, SignalForm_t form, double freq, double phase);
bool ad9833_set_form(uint8_t num, SignalForm_t form);
bool ad9833_set_freq(uint8_t num, RegNum_t reg_num, double freq);
bool ad9833_set_phase(uint8_t num, RegNum_t reg_num, double phase);

#endif /* AD9833_DRV_H */
