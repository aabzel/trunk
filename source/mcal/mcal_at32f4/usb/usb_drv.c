#include "usb_drv.h"
/**
  * @brief   This file provides code for the configuration
  *          of the USB_OTG instances.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  */

#include "usb_config.h"

#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif

#ifdef HAS_USB_HOST
#include "usb_host.h"
#endif


bool usb_init(void) {
    LOG_INFO(USB, "Init");
	bool res = false;
#ifdef HAS_USB_HOST
	res = usb_host_init();
#endif /*HAS_USB_HOST*/

#ifdef HAS_USB_DEVICE
	res = usb_device_init();
#endif /*HAS_USB_DEVICE*/

	return res;
}


#ifdef HAS_HCD
#error erer er
#endif
/* USB_OTG_FS init function */
#ifdef HAS_HCD
#endif
/* USB_OTG_HS init function */
#ifdef HAS_HCD
void MX_USB_OTG_HS_PCD_Init(void)
{

  hpcd_USB_OTG_HS.Instance = USB_OTG_HS;
  hpcd_USB_OTG_HS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_HS.Init.speed = PCD_SPEED_HIGH;
  hpcd_USB_OTG_HS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.phy_itface = USB_OTG_ULPI_PHY;
  hpcd_USB_OTG_HS.Init.Sof_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.vbus_sensing_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.use_dedicated_ep1 = DISABLE;
  hpcd_USB_OTG_HS.Init.use_external_vbus = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_HS) != HAL_OK)
  {
    Error_Handler();
  }

}
#endif

#ifdef HAS_HCD
void HAL_HCD_MspInit(HCD_HandleTypeDef* hcdHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hcdHandle->Instance==USB_OTG_FS)
  {
  /* USER CODE BEGIN USB_OTG_FS_MspInit 0 */

  /* USER CODE END USB_OTG_FS_MspInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USB_OTG_FS GPIO Configuration
    PA11     ------> USB_OTG_FS_DM
    PA12     ------> USB_OTG_FS_DP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USB_OTG_FS clock enable */
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    /* USB_OTG_FS interrupt Init */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
  /* USER CODE BEGIN USB_OTG_FS_MspInit 1 */

  /* USER CODE END USB_OTG_FS_MspInit 1 */
  }
}
#endif

#ifdef HAS_PCD
void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(pcdHandle->Instance==USB_OTG_HS)
  {
  /* USER CODE BEGIN USB_OTG_HS_MspInit 0 */

  /* USER CODE END USB_OTG_HS_MspInit 0 */

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USB_OTG_HS GPIO Configuration
    PC0     ------> USB_OTG_HS_ULPI_STP
    PC2     ------> USB_OTG_HS_ULPI_DIR
    PC3     ------> USB_OTG_HS_ULPI_NXT
    PA3     ------> USB_OTG_HS_ULPI_D0
    PA5     ------> USB_OTG_HS_ULPI_CK
    PB0     ------> USB_OTG_HS_ULPI_D1
    PB1     ------> USB_OTG_HS_ULPI_D2
    PB10     ------> USB_OTG_HS_ULPI_D3
    PB11     ------> USB_OTG_HS_ULPI_D4
    PB12     ------> USB_OTG_HS_ULPI_D5
    PB13     ------> USB_OTG_HS_ULPI_D6
    PB5     ------> USB_OTG_HS_ULPI_D7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USB_OTG_HS clock enable */
    __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
    __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE();

    /* USB_OTG_HS interrupt Init */
    HAL_NVIC_SetPriority(OTG_HS_EP1_OUT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OTG_HS_EP1_OUT_IRQn);
    HAL_NVIC_SetPriority(OTG_HS_EP1_IN_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OTG_HS_EP1_IN_IRQn);
    HAL_NVIC_SetPriority(OTG_HS_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
  /* USER CODE BEGIN USB_OTG_HS_MspInit 1 */

  /* USER CODE END USB_OTG_HS_MspInit 1 */
  }
}
#endif

#ifdef HAS_HCD
void HAL_HCD_MspDeInit(HCD_HandleTypeDef* hcdHandle)
{

  if(hcdHandle->Instance==USB_OTG_FS)
  {
    __HAL_RCC_USB_OTG_FS_CLK_DISABLE();

    /**USB_OTG_FS GPIO Configuration
    PA11     ------> USB_OTG_FS_DM
    PA12     ------> USB_OTG_FS_DP
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
  }
}
#endif

#ifdef HAS_PCD
void HAL_PCD_MspDeInit(PCD_HandleTypeDef* pcdHandle){
  if(pcdHandle->Instance==USB_OTG_HS)  {
    __HAL_RCC_USB_OTG_HS_CLK_DISABLE();
    __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE();

    /**USB_OTG_HS GPIO Configuration
    PC0     ------> USB_OTG_HS_ULPI_STP
    PC2     ------> USB_OTG_HS_ULPI_DIR
    PC3     ------> USB_OTG_HS_ULPI_NXT
    PA3     ------> USB_OTG_HS_ULPI_D0
    PA5     ------> USB_OTG_HS_ULPI_CK
    PB0     ------> USB_OTG_HS_ULPI_D1
    PB1     ------> USB_OTG_HS_ULPI_D2
    PB10     ------> USB_OTG_HS_ULPI_D3
    PB11     ------> USB_OTG_HS_ULPI_D4
    PB12     ------> USB_OTG_HS_ULPI_D5
    PB13     ------> USB_OTG_HS_ULPI_D6
    PB5     ------> USB_OTG_HS_ULPI_D7
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3|GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_5);

    HAL_NVIC_DisableIRQ(OTG_HS_EP1_OUT_IRQn);
    HAL_NVIC_DisableIRQ(OTG_HS_EP1_IN_IRQn);
    HAL_NVIC_DisableIRQ(OTG_HS_IRQn);
  }
}
#endif

UsbHandle_t* UsbGetNode(uint8_t usb_num) {
    UsbHandle_t* InstNode = NULL;
    uint32_t i = 0;
    uint32_t usb_cnt = usb_get_cnt();
    for(i = 0; i < usb_cnt; i++) {
        if(usb_num == UsbInstance[i].num) {
            if(UsbInstance[i].valid) {
                InstNode = &UsbInstance[i];
                break;
            }
        }
    }
    return InstNode;
}

UsbHandle_t* UsbGetNodeBySpeed(UsbSpeed_t speed){
	UsbHandle_t* InstNode = NULL;
    uint32_t i = 0;
    uint32_t usb_cnt = usb_get_cnt();
    for(i = 0; i < usb_cnt; i++) {
        if(speed == UsbConfig[i].speed) {
            if(UsbConfig[i].valid) {
            	InstNode = &UsbInstance[i];
                break;
            }
        }
    }
    return InstNode;
}

const UsbConfig_t* UsbGetConfNode(uint8_t usb_num) {
	const UsbConfig_t* ConfNode = NULL;
    uint32_t i = 0;
    uint32_t usb_cnt = usb_get_cnt();
    for(i = 0; i < usb_cnt; i++) {
        if(usb_num == UsbConfig[i].num) {
            if(UsbConfig[i].valid) {
            	ConfNode = &UsbConfig[i];
                break;
            }
        }
    }
    return ConfNode;
}


