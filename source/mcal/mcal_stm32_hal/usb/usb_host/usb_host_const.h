#ifndef USB_HOST_CONST_H
#define USB_HOST_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define USB_HOST_PERIOD_US 100

typedef enum { APPLICATION_IDLE = 0, APPLICATION_START, APPLICATION_READY, APPLICATION_DISCONNECT } ApplicationTypeDef;


#ifdef __cplusplus
}
#endif

#endif /* USB_HOST_CONST_H */
