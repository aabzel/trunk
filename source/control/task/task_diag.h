#ifndef TASK_DIAG_H
#define TASK_DIAG_H

#include <stdbool.h>

#include "task_types.h"

const char* TaskNode2Str(const TaskConfig_t* const Node);

bool task_diag_run(char* key_word1, char* key_word2);
bool task_diag(char* keyWord1, char* keyWord2);
bool task_diag_period(char* key_word1, char* key_word2);

#endif /* TASK_DIAG_H */
