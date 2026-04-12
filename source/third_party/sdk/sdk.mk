ifneq ($(VENDOR_SDK_MK_INC),Y)
    VENDOR_SDK_MK_INC=Y

    VENDOR_SDK_DIR = $(THIRD_PARTY_DIR)/sdk
    # $(error VENDOR_SDK_DIR= $(VENDOR_SDK_DIR))

    VENDOR_SDK_DIR:= $(realpath $(VENDOR_SDK_DIR))
    VENDOR_SDK_DIR := $(subst /cygdrive/c/,C:/, $(VENDOR_SDK_DIR))
    # $(error VENDOR_SDK_DIR= $(VENDOR_SDK_DIR))


    INCDIR += -I$(VENDOR_SDK_DIR)
    MCAL_OPT += -DHAS_VENDOR_SDK

    ifeq ($(CMSIS),Y)
        # $(error CMSIS=$(CMSIS))
        include $(VENDOR_SDK_DIR)/CMSIS/cmsis.mk
    endif

    ifeq ($(AT32F413_FIRMWARE_LIBRARY_V2_1_4_EN),Y)
        # $(error AT32F413_FIRMWARE_LIBRARY_V2_1_4_EN=$(AT32F413_FIRMWARE_LIBRARY_V2_1_4_EN))
        include $(VENDOR_SDK_DIR)/AT32F413_Firmware_Library_V2_1_4_EN/AT32F413_Firmware_Library_V2_1_4_EN.mk
    endif

    ifeq ($(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5),Y)
        # $(error AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5=$(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5))
        include $(VENDOR_SDK_DIR)/AT32F435_437_Firmware_Library_EN_V2.1.5/AT32F435_437_Firmware_Library_EN_V2_1_5.mk
    endif

    ifeq ($(FC7300_SDK_V2_3_2),Y)
        # $(error FC7300_SDK_V2_3_2=$(FC7300_SDK_V2_3_2))
        include $(VENDOR_SDK_DIR)/FC7300_SDK_V2_3_2/FC7300_SDK_V2_3_2.mk
    endif

    ifeq ($(FC7300_SDK_V2_4_0),Y)
        # $(error FC7300_SDK_V2_4_0=$(FC7300_SDK_V2_4_0))
        include $(VENDOR_SDK_DIR)/FC7300_SDK_V2_4_0/FC7300_SDK_V2_4_0.mk
    endif
    
    ifeq ($(MIK32),Y)
        # $(error MIK32=$(MIK32))
        include $(VENDOR_SDK_DIR)/MIK32_HAL/MIK32_SRC.mk
    endif
    
    ifeq ($(EHAL_AT32F413X),Y)
        # $(error EHAL_AT32F413X=$(EHAL_AT32F413X))
        include $(VENDOR_SDK_DIR)/EHAL_AT32F413x/EHAL_AT32F413x.mk
    endif

    ifeq ($(EHAL_AT32F43X),Y)
        # $(error EHAL_AT32F43X=$(EHAL_AT32F43X))
        include $(VENDOR_SDK_DIR)/EHAL_AT32F43x/EHAL_AT32F43x.mk
    endif

    ifeq ($(EHAL_YTM32B1Mx),Y)
        # $(error EHAL_YTM32B1Mx=$(EHAL_YTM32B1Mx))
        include $(VENDOR_SDK_DIR)/EHAL_YTM32B1Mx/EHAL_YTM32B1Mx.mk
    endif

    ifeq ($(SIMPLELINK_CC13X2_26X2_SDK),Y)
        # $(error SIMPLELINK_CC13X2_26X2_SDK=$(SIMPLELINK_CC13X2_26X2_SDK))
        include $(VENDOR_SDK_DIR)/simplelink_cc13x2_26x2_sdk/simplelink_cc13x2_26x2_sdk.mk
    endif

    ifeq ($(STM32F4XX_HAL_DRIVER),Y)
        #$(error STM32F4XX_HAL_DRIVER=$(STM32F4XX_HAL_DRIVER))
        include $(VENDOR_SDK_DIR)/STM32F4xx_HAL_Driver/stm32f4xx_hal_driver.mk
    endif

    ifeq ($(STM32F4XX_HAL_DRIVER_RI),Y)
        #$(error STM32F4XX_HAL_DRIVER_RI=$(STM32F4XX_HAL_DRIVER_RI))
        include $(VENDOR_SDK_DIR)/STM32F4xx_HAL_Driver_RI/stm32f4xx_hal_driver.mk
    endif

    ifeq ($(STM32),Y)
        ifeq ($(USB_DEVICE_RI),Y)
            # $(error USB_DEVICE=$(USB_DEVICE))
            #include $(VENDOR_SDK_DIR)/STM32_USB_Device_Library_V1/STM32_USB_Device_Library.mk
            #include $(VENDOR_SDK_DIR)/STM32_USB_Device_Library/STM32_USB_Device_Library.mk
            include $(VENDOR_SDK_DIR)/STM32_USB_Device_Library_RI/STM32_USB_Device_Library.mk
        endif

        ifeq ($(USB_DEVICE),Y)
            # $(error USB_DEVICE=$(USB_DEVICE))
           #include $(VENDOR_SDK_DIR)/STM32_USB_Device_Library_V1/STM32_USB_Device_Library.mk
            include $(VENDOR_SDK_DIR)/STM32_USB_Device_Library/STM32_USB_Device_Library.mk
        endif

        ifeq ($(USB_HOST),Y)
            # $(error USB_DEVICE=$(USB_DEVICE))
            include $(VENDOR_SDK_DIR)/STM32_USB_Host_Library/STM32_USB_Host_Library.mk
        endif
    endif

    ifeq ($(YTM32B1ME0_1_3_1),Y)
        # $(error YTM32B1ME0_1_3_1=$(YTM32B1ME0_1_3_1))
        include $(VENDOR_SDK_DIR)/YTM32B1ME0_1_3_1/YTM32B1ME0_1_3_1.mk
    endif
    
endif