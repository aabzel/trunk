#include "usb_mcal.h"

#include "usb_config.h"
#include "code_generator.h"

#ifdef HAS_USB_SERIAL
#include "usb_serial.h"
#endif

#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif

#ifdef HAS_USB_HOST
#include "usb_host.h"
#endif

static const UsbInfo_t UsbInfo[] = {
    {
        .num = 1,
        .valid = true,
        .USBx = USB_OTG_FS,
    },
    {
        .num = 2,
        .valid = true,
        .USBx = USB_OTG_HS,
    },
};

COMPONENT_GET_INFO(Usb)


bool usb_device_mcal_init(void) {
    LOG_INFO(USB, "DevInit");
    bool res = false;

#ifdef HAS_USB_SERIAL
    //res = usb_serial_init(1);
#endif

#ifdef HAS_USB_DEVICE
    res = usb_device_init(1);
#endif

    return res;
}

bool usb_init_clock(const UsbHandle_t* const Node ){
    bool res = false;
    switch(Node->device_speed){
    case USB_DEVICE_SPEED_FS:{
        __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
    } break;
    case USB_DEVICE_SPEED_HS:{
        __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
    } break;
    default : res = false; break;
    }
    return res;
}

bool usb_init_common(const UsbConfig_t* const Config,
                     UsbHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->device_speed = Config->device_speed;
            Node->PadDP = Config->PadDP;
            Node->PadDM = Config->PadDM;
            Node->host_speed = Config->host_speed;
            Node->Descriptors = Config->Descriptors;
            Node->num = Config->num;
            Node->role = Config->role;
            Node->interrupt_on = Config->interrupt_on;
            Node->speed = Config->speed;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}


bool usb_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(USB, "USB%u", num);
    const UsbConfig_t* Config = UsbGetConfig(num);
    if(Config) {
        res = UsbIsValidConfig(Config);
        if(res) {
#ifdef HAS_USB_DIAG
            LOG_WARNING(USB, "%s", UsbConfigToStr(Config));
#endif
            UsbHandle_t* Node = UsbGetNode(num);
            if(Node) {
                res = usb_init_common(Config,Node);

                switch(Node->role) {
                    case USB_MCAL_ROLE_HOST: {
#ifdef HAS_USB_HOST
                        res = usb_host_init();
#endif

                    }break;
                    case USB_MCAL_ROLE_DEVICE: {
#ifdef HAS_USB_DEVICE
                       res = usb_device_init(num);
#endif

                    }break;
                    default: break;
                }
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(USB, "NodeErr:%u", num);
            }
        } else {
            LOG_ERROR(USB, "ConfigErr:%u", num);
        }
    } else {
        LOG_PARN(USB, "ConfigErr:%u", num);
    }
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
void MX_USB_OTG_HS_PCD_Init(void) {

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
    if(HAL_PCD_Init(&hpcd_USB_OTG_HS) != HAL_OK) {
        Error_Handler();
    }
}
#endif

#ifdef HAS_HCD
void HAL_HCD_MspInit(HCD_HandleTypeDef* hcdHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hcdHandle->Instance == USB_OTG_FS) {
        /* USER CODE BEGIN USB_OTG_FS_MspInit 0 */

        /* USER CODE END USB_OTG_FS_MspInit 0 */

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USB_OTG_FS GPIO Configuration
        PA11     ------> USB_OTG_FS_DM
        PA12     ------> USB_OTG_FS_DP
        */
        GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
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
void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(pcdHandle->Instance == USB_OTG_HS) {
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
        GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin =
            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_5;
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
void HAL_HCD_MspDeInit(HCD_HandleTypeDef* hcdHandle) {

    if(hcdHandle->Instance == USB_OTG_FS) {
        __HAL_RCC_USB_OTG_FS_CLK_DISABLE();

        /**USB_OTG_FS GPIO Configuration
        PA11     ------> USB_OTG_FS_DM
        PA12     ------> USB_OTG_FS_DP
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);

        HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
    }
}
#endif

#ifdef HAS_PCD
void HAL_PCD_MspDeInit(PCD_HandleTypeDef* pcdHandle) {
    if(pcdHandle->Instance == USB_OTG_HS) {
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
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3 | GPIO_PIN_5);

        HAL_GPIO_DeInit(GPIOB,
                        GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_5);

        HAL_NVIC_DisableIRQ(OTG_HS_EP1_OUT_IRQn);
        HAL_NVIC_DisableIRQ(OTG_HS_EP1_IN_IRQn);
        HAL_NVIC_DisableIRQ(OTG_HS_IRQn);
    }
}
#endif

UsbHandle_t* UsbGetNodeBySpeed(UsbSpeed_t speed) {
    UsbHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t usb_cnt = usb_get_cnt();
    for(i = 0; i < usb_cnt; i++) {
        if(speed == UsbConfig[i].speed) {
            if(UsbConfig[i].valid) {
                Node = &UsbInstance[i];
                break;
            }
        }
    }
    return Node;
}

bool usb_proc_one(const uint8_t num) {
    bool res = false;
    LOG_PARN(USB, "Proc:%u", num);
    UsbHandle_t* Node = UsbGetNode(num);
    if(Node) {
#ifdef HAS_USB_DEVICE
        res = usb_device_proc_one(num);
#endif
        Node->spin++;
    }
    return res;
}
