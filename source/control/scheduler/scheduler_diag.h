#ifndef SCHEDULER_DIAG_H
#define SCHEDULER_DIAG_H

#include <stdbool.h>

#include "scheduler_types.h"


const char* SchedulerTaskToStr(const SchedulerTaskHandle_t* const Task);
const char* SchedulerNodeToStr(const SchedulerHandle_t* const Node);


const char* TaskNumToName(const uint8_t num, const uint32_t task_num);
bool scheduler_diag_run(const uint8_t num, char* key_word1, char* key_word2);
bool scheduler_diag(const uint8_t num, char* keyWord1, char* keyWord2);
bool scheduler_diag_period(const uint8_t num, char* key_word1, char* key_word2);

#endif /* SCHEDULER_DIAG_H */
