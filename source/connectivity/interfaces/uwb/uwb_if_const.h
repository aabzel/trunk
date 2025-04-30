#ifndef UWB_IF_CONST_H
#define UWB_IF_CONST_H

#include "time_mcal.h"

#define UWB_DIST_UPDATE_TIMEOUT_MS SEC_2_MSEC(10)

typedef enum {
    UWB_ROLE_ANCOR = 1, /*RESPONDER*/
    UWB_ROLE_TAG = 2,   /*INITIATOR*/

    UWB_ROLE_UNDEF = 0,
} UwbRole_t;


typedef enum {
    ID_STATUS_REAL = 2,
    ID_STATUS_STATIC = 1,

    ID_STATUS_UNDEF = 0,
} IdStatus_t;


#endif /* UWB_IF_CONST_H  */
