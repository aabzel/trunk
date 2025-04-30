#ifndef RUNNING_LINE_H
#define RUNNING_LINE_H

#include "std_includes.h"

#include "running_line_config.h"
#include "running_line_types.h"
#ifdef HAS_RUNNING_LINE_DIAG
#include "running_line_diag.h"
#endif

RunningLineHandle_t* RunningLineGetNode(uint8_t num);
const RunningLineConfig_t* RunningLineGetConfig(uint8_t num) ;

bool running_line_mcal_init(void);
bool running_line_proc(void);
bool running_line_init_one(uint8_t num);

const char* running_line_get_text(uint8_t num);
bool running_line_set_text(uint8_t num, const char* const text);
bool running_line_add_suffix(uint8_t num, const char* const suffix);
bool running_line_add_prefix(uint8_t num, const char* const prefix);

//uint32_t running_line_get_cnt(void);

#endif /* RUNNING_LINE_H  */
