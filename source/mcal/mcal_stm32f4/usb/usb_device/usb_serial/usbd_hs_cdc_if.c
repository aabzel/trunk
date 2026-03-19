/*  Usb device for Virtual Com Port. */
#include "usbd_hs_cdc_if.h"

#include "usb_mcal.h"
#include "log.h"
#include "string_reader.h"
#include "fifo_char.h"
#include "usb_serial.h"
#include "usb_device.h"

/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferHS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferHS[APP_TX_DATA_SIZE];

//extern USBD_HandleTypeDef Node->hUsbDevice;





/**
  * @brief  Initializes the CDC media low layer over the USB HS IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_HS(void) {
    UsbHandle_t* Node = UsbGetNode(USB_DEVICE_NUM);
    if (Node) {
        /* Set Application Buffers */
        USBD_CDC_SetTxBuffer(&Node->hUsbDevice, UserTxBufferHS, 0);
        USBD_CDC_SetRxBuffer(&Node->hUsbDevice, UserRxBufferHS);
    }
    return (USBD_OK);
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @param  None
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_HS(void){
  return (USBD_OK);
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_HS(uint8_t cmd, uint8_t* pbuf, uint16_t length) {
  /* USER CODE BEGIN 10 */
  switch(cmd)   {
  case CDC_SEND_ENCAPSULATED_COMMAND:    break;
  case CDC_GET_ENCAPSULATED_RESPONSE:    break;
  case CDC_SET_COMM_FEATURE:    break;
  case CDC_GET_COMM_FEATURE:    break;
  case CDC_CLEAR_COMM_FEATURE:    break;

  /*******************************************************************************/
  /* Line Coding Structure                                                       */
  /*-----------------------------------------------------------------------------*/
  /* Offset | Field       | Size | Value  | Description                          */
  /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
  /* 4      | bCharFormat |   1  | Number | Stop bits                            */
  /*                                        0 - 1 Stop bit                       */
  /*                                        1 - 1.5 Stop bits                    */
  /*                                        2 - 2 Stop bits                      */
  /* 5      | bParityType |  1   | Number | Parity                               */
  /*                                        0 - None                             */
  /*                                        1 - Odd                              */
  /*                                        2 - Even                             */
  /*                                        3 - Mark                             */
  /*                                        4 - Space                            */
  /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
  /*******************************************************************************/
  case CDC_SET_LINE_CODING:    break;
  case CDC_GET_LINE_CODING:    break;
  case CDC_SET_CONTROL_LINE_STATE:    break;
  case CDC_SEND_BREAK:    break;
  default:    break;
  }

  return USBD_OK;
}

/**
  * @brief Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint until exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAILL
  */
const InterfaceType_t interface_if = {.num = 1, .interface_name = INTERFACE_NAME_USB, };
static int8_t CDC_Receive_HS(uint8_t* Buf, uint32_t* Len) {
    writer_interface_set(interface_if);
    int8_t status = USBD_FAIL;
    bool res = false;
    (void) res;
    LOG_PARN(USB_SERIAL, "RxData:%c,Len:%u", *Buf, *Len);
    UsbHandle_t *Node = UsbGetNode(USB_DEVICE_NUM);
    if (Node) {
        Node->rx_len = *Len;
        if(   (*Len)  <=  sizeof(Node->RxData)   ) {
            memcpy(Node->RxData, Buf, *Len);
        }

#ifdef HAS_STRING_READER
        uint32_t i = 0;
        for(i=0; i<Node->rx_len; i++) {
            res = string_reader_rx_byte(interface_if, Buf[i]);
        }
#endif
        USBD_CDC_SetRxBuffer(&Node->hUsbDevice, &Buf[0]);
        USBD_CDC_ReceivePacket(&Node->hUsbDevice);
        status = USBD_OK;
    }
    return status;
}

/**
  * @brief  Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_HS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  UsbHandle_t *Node = UsbGetNode(USB_DEVICE_NUM);
  if(Node) {
      USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)Node->hUsbDevice.pClassData;
      if (hcdc->TxState != 0){
        return USBD_BUSY;
      }
      USBD_CDC_SetTxBuffer(&Node->hUsbDevice, Buf, Len);
      result = USBD_CDC_TransmitPacket(&Node->hUsbDevice);
  }
  return result;
}



/**
  * @brief  CDC_TransmitCplt_HS
  *         Data transmitted callback
  *
  *         @note
  *         This function is IN transfer complete callback used to inform user that
  *         the submitted Data is successfully sent over USB.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_TransmitCplt_HS(uint8_t* Buf, uint32_t* Len, uint8_t epnum) {
    uint8_t result = USBD_OK;
    UNUSED(Buf);
    UNUSED(Len);
    UNUSED(epnum);
    UsbHandle_t *Node = UsbGetNode(USB_DEVICE_NUM);
    if (Node) {
        Node->tx_in_progress = false ;
        Node->tx_done = true;
        Node->tx_cnt++;
        bool res = false;
        uint32_t out_len = 0;
        res = fifo_pull_array(&Node->TxFifo, Node->TxBuff, sizeof(Node->TxBuff), &out_len);
        if (res) {
            if(out_len){
                res = usb_serial_send(1, Node->TxBuff, out_len);
                result = usb_device_res_to_ret(res);
            }
        }
    }
    return result;
}

USBD_CDC_ItfTypeDef USBD_Interface_fops_HS = {
    .Init = CDC_Init_HS,
    .DeInit = CDC_DeInit_HS,
    .Control = CDC_Control_HS,
    .Receive = CDC_Receive_HS,
    .TransmitCplt = CDC_TransmitCplt_HS
};
