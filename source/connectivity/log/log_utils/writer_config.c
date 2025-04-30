#include "writer_config.h"

#ifdef HAS_UART
generic_writer_t* curWriterPtr = &dbg_o;
#else /*HAS_UART*/

#ifdef HAS_SWD
generic_writer_t* curWriterPtr = &swd_o;
#else  /*HAS_SWD*/
generic_writer_t* curWriterPtr = NULL;
#endif /*HAS_SWD*/

#endif /*HAS_UART*/
