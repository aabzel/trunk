#ifndef SSD1306_TYPES_H
#define SSD1306_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "ssd1306_const.h"

#define SSD1306_CONNON_VARIABLES                       \
    uint8_t num;                                       \
    uint8_t i2c_num;                                   \
    uint8_t i2c_addr;                                  \
    Ssd1306MemoryAddressingMode_t mem_addressing_mode; \
    bool valid;

typedef struct {
	SSD1306_CONNON_VARIABLES
	char* name[10];
}Ssd1306Config_t;

typedef struct {
	SSD1306_CONNON_VARIABLES
    bool init;
    uint32_t err_cnt;
	uint8_t FrameBuffer[FRAME_BUFFER_SIZE+1];
}Ssd1306Handle_t;


typedef union{
	uint8_t byte;
	struct{
		uint8_t control:6;
		uint8_t data_command_sel:1;  /*0-cmd 1-data*/
		uint8_t continuation:1; /*If the Co bit is set as logic “0”, the
		                transmission of the following information will contain
                        data bytes only.*/
	};
}ControlByte_t;

typedef union{
	uint8_t byte;
	struct{
		uint8_t divide_ratio:4;
		uint8_t oscillator_frequency:4;
	};
}DivideRatio_t;

#endif /* SSD1306_TYPES_H */
