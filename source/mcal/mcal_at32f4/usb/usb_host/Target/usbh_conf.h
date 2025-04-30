#ifndef USB_HOST_CONF_H
#define USB_HOST_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stm32f4xx.h"
#include "artery_at32f4xx.h"

//extern HCD_HandleTypeDef hhcd_USB_OTG;

#define USBH_MAX_NUM_ENDPOINTS      2U
#define USBH_MAX_NUM_INTERFACES      2U
#define USBH_MAX_NUM_CONFIGURATION      1U
#define USBH_KEEP_CFG_DESCRIPTOR      1U
#define USBH_MAX_NUM_SUPPORTED_CLASS      1U
#define USBH_MAX_SIZE_CONFIGURATION      256U
#define USBH_MAX_DATA_BUFFER      512U
#define USBH_DEBUG_LEVEL      0U
#define USBH_USE_OS      0U

/* #define for FS and HS identification */
#define HOST_HS 		0
#define HOST_FS 		1

#if (1==USBH_USE_OS)
  #include "cmsis_os.h"
  #define USBH_PROCESS_PRIO          osPriorityNormal
  #define USBH_PROCESS_STACK_SIZE    ((uint16_t)0)
#endif /* (USBH_USE_OS == 1) */

#define USBH_malloc         malloc
#define USBH_free           free
#define USBH_memset         memset
#define USBH_memcpy         memcpy

#if (USBH_DEBUG_LEVEL > 0U)
#define  USBH_UsrLog(...)   do { \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBH_UsrLog(...) do {} while (0)
#endif

#if (USBH_DEBUG_LEVEL > 1U)

#define  USBH_ErrLog(...) do { \
                            printf("ERROR: ") ; \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBH_ErrLog(...) do {} while (0)
#endif

#if (USBH_DEBUG_LEVEL > 2U)
#define  USBH_DbgLog(...)   do { \
                            printf("DEBUG : ") ; \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBH_DbgLog(...) do {} while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* USB_HOST_CONF_H */

