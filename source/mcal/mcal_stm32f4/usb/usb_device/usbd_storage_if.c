/**
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @version        : v1.0_Cube
  * @brief          : Memory management layer.
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  */
/* USER CODE END Header */

#include "usbd_storage_if.h"
#include "log.h"

#ifdef HAS_SDIO
#include "sdio_drv.h"
#endif

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @defgroup USBD_STORAGE
  * @brief Usb mass storage device module
  * @{
  */

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/** @defgroup USBD_STORAGE_Private_Defines
  * @brief Private defines.
  * @{
  */

#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  0x10000
#define STORAGE_BLK_SIZ                  0x200


/** @defgroup USBD_STORAGE_Private_Macros
  * @brief Private macros.
  * @{
  */


/** @defgroup USBD_STORAGE_Private_Variables
  * @brief Private variables.
  * @{
  */

/* USER CODE BEGIN INQUIRY_DATA_HS */
/** USB Mass storage Standard Inquiry Data. */
const int8_t STORAGE_Inquirydata_HS[] = {/* 36 */

  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
};


extern USBD_HandleTypeDef hUsbDeviceHS;

static int8_t STORAGE_Init_HS(uint8_t lun);
static int8_t STORAGE_GetCapacity_HS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t STORAGE_IsReady_HS(uint8_t lun);
static int8_t STORAGE_IsWriteProtected_HS(uint8_t lun);
static int8_t STORAGE_Read_HS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_Write_HS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_HS(void);


USBD_StorageTypeDef USBD_Storage_Interface_fops_HS = {
  STORAGE_Init_HS,
  STORAGE_GetCapacity_HS,
  STORAGE_IsReady_HS,
  STORAGE_IsWriteProtected_HS,
  STORAGE_Read_HS,
  STORAGE_Write_HS,
  STORAGE_GetMaxLun_HS,
  (int8_t *)STORAGE_Inquirydata_HS
};


/**
  * @brief  Initializes the storage unit (medium).
  * @param  lun: Logical unit number.
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Init_HS(uint8_t lun) {
  UNUSED(lun);
  return (USBD_OK);
}

/**
  * @brief  Returns the medium capacity.
  * @param  lun: Logical unit number.
  * @param  block_num: Number of total block number.
  * @param  block_size: Block size.
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_GetCapacity_HS(uint8_t lun,
		uint32_t *block_num,
		uint16_t *block_size){
  UNUSED(lun);
#ifdef HAS_SDIO
    *block_num  = sdio_get_block_num(SD_CARD_SDIO_NUM);
    *block_size =  sdio_get_block_size(SD_CARD_SDIO_NUM);
#else
    *block_num  = STORAGE_BLK_NBR;
    *block_size = STORAGE_BLK_SIZ;
#endif

  return (USBD_OK);
}

/**
  * @brief   Checks whether the medium is ready.
  * @param  lun:  Logical unit number.
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsReady_HS(uint8_t lun) {
  UNUSED(lun);

  return (USBD_OK);
}

/**
  * @brief  Checks whether the medium is write protected.
  * @param  lun: Logical unit number.
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsWriteProtected_HS(uint8_t lun) {
  return (USBD_OK);
}

/**
  * @brief  Reads data from the medium.
  * @param  lun: Logical unit number.
  * @param  buf: data buffer.
  * @param  blk_addr: Logical block address.
  * @param  blk_len: Blocks number.
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Read_HS(uint8_t lun,
		uint8_t *buf,
		uint32_t blk_addr,
		uint16_t blk_len) {
    USBD_StatusTypeDef ret=USBD_FAIL;
    UNUSED(lun);
#ifdef HAS_SDIO
    bool res = false;
    res= sdio_read_sector(SD_CARD_SDIO_NUM,
  		blk_addr,
  		blk_len,
  		(uint8_t* const) buf);
    if(res) {
        ret = USBD_OK;
    }else {
        LOG_ERROR(MSD,"ReadErr");
    }
#endif
    return ret;
}

/**
  * @brief  Writes data into the medium.
  * @param  lun: Logical unit number.
  * @param  buf: data buffer.
  * @param  blk_addr: Logical block address.
  * @param  blk_len: Blocks number.
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Write_HS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len){
    UNUSED(lun);
    USBD_StatusTypeDef ret=USBD_FAIL;

#ifdef HAS_SDIO
    bool res = false;
    res = sdio_write_sector(SD_CARD_SDIO_NUM,  blk_addr,
		  blk_len, (const uint8_t* const) buf);
    if(res) {
	  ret=USBD_OK;
    }else {
	  ret=USBD_FAIL;
    }
#endif
    return ret;
}

/**
  * @brief  Returns the Max Supported LUNs.
  * @param  None
  * @retval Lun(s) number.
  */
int8_t STORAGE_GetMaxLun_HS(void){
    return (STORAGE_LUN_NBR - 1);
}


