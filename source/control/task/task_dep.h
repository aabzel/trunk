#ifndef TASK_DEP_H
#define TASK_DEP_H

#ifndef HAS_TASK
#error "+ HAS_TASK"
#endif /*HAS_TASK*/

#ifndef HAS_TIME
#warning "+ HAS_TIME"
#endif /*HAS_TIME*/

#ifndef HAS_FLASH
#warning "+ HAS_FLASH"
#endif /*HAS_FLASH*/

#ifndef HAS_LIMITER
#error "+ HAS_LIMITER"
#endif /*HAS_LIMITER*/

#endif /* TASK_DEP_H */
