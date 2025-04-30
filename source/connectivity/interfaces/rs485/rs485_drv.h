#ifndef RS485_SCAN
#define RS485_SCAN

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdint.h>


bool rs485_scan(void);
bool rs485_init(void);

#ifdef __cplusplus
}
#endif

#endif /* RS485_SCAN  */
