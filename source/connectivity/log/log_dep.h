#ifndef LOG_DEP_H
#define LOG_DEP_H

#ifndef HAS_TIME
#warning "+ TIME componet for time stamp"
#endif

#ifndef HAS_LOG
#error "+ HAS_LOG"
#endif

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif


#endif /* LOG_DEP_H */
