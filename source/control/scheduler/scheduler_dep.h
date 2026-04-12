#ifndef SCHEDULER_DEP_H
#define SCHEDULER_DEP_H

#ifndef HAS_SCHEDULER
#error "+ HAS_SCHEDULER"
#endif /**/

#ifndef HAS_TIME
#warning "+ HAS_TIME"
#endif /**/

#ifndef HAS_FLASH
#warning "+ HAS_FLASH"
#endif /**/

#ifndef HAS_LIMITER
#error "+ HAS_LIMITER"
#endif /**/

#endif /* SCHEDULER_DEP_H */
