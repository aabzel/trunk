#ifndef CORE_DEPEN_H
#define CORE_DEPEN_H

#ifdef HAS_CORTEX_M4
#ifdef HAS_CORTEX_M33
#error  "Core contradiction!"
#endif
#endif

#ifdef HAS_CORTEX_M7
#ifdef HAS_CORTEX_M33
#error  "Core contradiction!"
#endif
#endif

#ifdef HAS_CORTEX_M4
#ifdef HAS_CORTEX_M7
#error  "Core contradiction!"
#endif
#endif



#endif /* CORE_DEPEN_H */
