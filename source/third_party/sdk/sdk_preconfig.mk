
ifneq ($(SDK_PRECONFIG_INC),Y)
    SDK_PRECONFIG_INC=Y

    SDK_DIR = $(THIRD_PARTY_DIR)/sdk
    # $(error SDK_DIR= $(SDK_DIR))

    ifeq ($(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5),Y)
        # $(error AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5=$(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5))
        include $(SDK_DIR)/AT32F435_437_Firmware_Library_EN_V2.1.5/AT32F435_437_Firmware_Library_EN_V2_1_5_preconfig.mk
    endif

    ifeq ($(CMSIS),Y)
        # $(error CMSIS=$(CMSIS))
        include $(SDK_DIR)/CMSIS/cmsis_preconfig.mk
    endif

    ifeq ($(EHAL_AT32F413),Y)
        # $(error EHAL_AT32F413=$(EHAL_AT32F413))
        include $(SDK_DIR)/EHAL_AT32F413x/EHAL_AT32F413_preconfig.mk
    endif
    
    ifeq ($(EHAL_AT32F43X),Y)
        # $(error EHAL_AT32F43X=$(EHAL_AT32F43X))
        include $(SDK_DIR)/EHAL_AT32F43X/EHAL_AT32F43X_preconfig.mk
    endif

    ifeq ($(EHAL_YTM32B1MX),Y)
        # $(error EHAL_YTM32B1MX=$(EHAL_YTM32B1MX))
        include $(SDK_DIR)/EHAL_YTM32B1Mx/EHAL_YTM32B1M_preconfig.mk
    endif

endif