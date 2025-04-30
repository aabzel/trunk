#ifndef CONNECTIVITY_TASKS_H
#define CONNECTIVITY_TASKS_H


#ifdef HAS_INTERFACES
#include "interfaces_tasks.h"
#else
#define INTERFACES_TASKS
#endif

#ifdef HAS_PROTOCOLS
#include "protocols_tasks.h"
#else
#define PROTOCOlS_TASKS
#endif

#define CONNECTIVITY_TASKS       \
    INTERFACES_TASKS             \
    PROTOCOlS_TASKS

#endif /* CONNECTIVITY_TASKS_H */
