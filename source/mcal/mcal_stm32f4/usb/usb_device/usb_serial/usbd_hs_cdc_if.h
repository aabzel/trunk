/**
  * @version        : v1.0_Cube
  * @brief          : Header for usbd_cdc_if.c file.
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  */

#ifndef __USBD_CDC_IF_H__
#define __USBD_CDC_IF_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "usbd_cdc.h"

/* Define size for the receive and transmit buffer over CDC */
#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048

 /** CDC Interface callback. */
extern USBD_CDC_ItfTypeDef USBD_Interface_fops_HS;

uint8_t CDC_Transmit_HS(uint8_t* Buf, uint16_t Len);


#ifdef __cplusplus
}
#endif

#endif /* __USBD_CDC_IF_H__ */

