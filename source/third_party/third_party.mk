ifneq ($(THIRD_PARTY_MK_INC),Y)
    THIRD_PARTY_MK_INC=Y

    THIRD_PARTY_DIR = $(WORKSPACE_LOC)/third_party
    #@echo $(error THIRD_PARTY_DIR= $(THIRD_PARTY_DIR))

    INCDIR += -I$(THIRD_PARTY_DIR)
    
    ifeq ($(MIK32),Y)
        #@echo $(error MIK32=$(MIK32))
        include $(THIRD_PARTY_DIR)/MIK32_HAL/MIK32_SRC.mk
    endif
    
    ifeq ($(AT32F413_FIRMWARE_LIBRARY_V2_1_4_EN),Y)
        #@echo $(error AT32F413_FIRMWARE_LIBRARY_V2_1_4_EN=$(AT32F413_FIRMWARE_LIBRARY_V2_1_4_EN))
        include $(THIRD_PARTY_DIR)/AT32F413_Firmware_Library_V2_1_4_EN/AT32F413_Firmware_Library_V2_1_4_EN.mk
    endif

    ifeq ($(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5),Y)
        #@echo $(error AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5=$(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5))
        include $(THIRD_PARTY_DIR)/AT32F435_437_Firmware_Library_EN_V2.1.5/AT32F435_437_Firmware_Library_EN_V2_1_5.mk
    endif

    ifeq ($(YTM32B1ME0_1_3_1),Y)
        #@echo $(error YTM32B1ME0_1_3_1=$(YTM32B1ME0_1_3_1))
        include $(THIRD_PARTY_DIR)/YTM32B1ME0_1_3_1/YTM32B1ME0_1_3_1.mk
    endif

    ifeq ($(FAT_FS),Y)
        #@echo $(error FAT_FS=$(FAT_FS))
        include $(THIRD_PARTY_DIR)/fat_fs/fat_fs.mk
    endif

    ifeq ($(FREE_RTOS),Y)
        #@echo $(error FREE_RTOS=$(FREE_RTOS))
        include $(THIRD_PARTY_DIR)/FreeRTOS/free_rtos.mk
    endif

    ifeq ($(SIMPLELINK_CC13X2_26X2_SDK),Y)
        #@echo $(error SIMPLELINK_CC13X2_26X2_SDK=$(SIMPLELINK_CC13X2_26X2_SDK))
        include $(THIRD_PARTY_DIR)/simplelink_cc13x2_26x2_sdk/simplelink_cc13x2_26x2_sdk.mk
    endif

    ifeq ($(CMSIS),Y)
        include $(THIRD_PARTY_DIR)/CMSIS/cmsis.mk
    endif

    ifeq ($(STM32),Y)
        #@echo $(error STM32=$(STM32))
        include $(THIRD_PARTY_DIR)/STM32F4xx_HAL_Driver/stm32f4xx_hal_driver.mk
    endif

    ifeq ($(STM32),Y)
        ifeq ($(USB_DEVICE),Y)
            #@echo $(error USB_DEVICE=$(USB_DEVICE))
            include $(THIRD_PARTY_DIR)/STM32_USB_Device_Library_V1/STM32_USB_Device_Library.mk
            #include $(THIRD_PARTY_DIR)/STM32_USB_Device_Library/STM32_USB_Device_Library.mk
        endif

        ifeq ($(USB_HOST),Y)
            #@echo $(error USB_DEVICE=$(USB_DEVICE))
            include $(THIRD_PARTY_DIR)/STM32_USB_Host_Library/STM32_USB_Host_Library.mk
        endif
    endif
    
    ifeq ($(THIRD_PARTY_ASICS),Y)
        include $(THIRD_PARTY_DIR)/asics/asics.mk
    endif
    
    ifeq ($(THIRD_PARTY_CONNECTIVITY),Y)
        #@echo $(error THIRD_PARTY_CONNECTIVITY=$(THIRD_PARTY_CONNECTIVITY))
        include $(THIRD_PARTY_DIR)/connectivity/connectivity.mk
    endif
    
    ifeq ($(THIRD_PARTY_COMPUTING),Y)
        #@echo $(error THIRD_PARTY_COMPUTING=$(THIRD_PARTY_COMPUTING))
        include $(THIRD_PARTY_DIR)/computing/computing.mk
    endif
    
    
    ifeq ($(THIRD_PARTY_STORAGE),Y)
        #@echo $(error THIRD_PARTY_STORAGE=$(THIRD_PARTY_STORAGE))
        include $(THIRD_PARTY_DIR)/storage/storage.mk
    endif
endif