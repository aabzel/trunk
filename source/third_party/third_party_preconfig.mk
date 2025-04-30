
ifneq ($(THIRD_PARTY_PRECONFIG_INC),Y)
    THIRD_PARTY_PRECONFIG_INC=Y

    THIRD_PARTY_DIR = $(WORKSPACE_LOC)/third_party
    #@echo $(error THIRD_PARTY_DIR= $(THIRD_PARTY_DIR))

    INCDIR += -I$(THIRD_PARTY_DIR)

    ifeq ($(ASICS),Y)
        #@echo $(error ASICS=$(ASICS))
        include $(THIRD_PARTY_DIR)/asics/asics_preconfig.mk
    endif

    ifeq ($(SERVICES),Y)
        #@echo $(error SERVICES=$(SERVICES))
        include $(THIRD_PARTY_DIR)/Services/Services_preconfig.mk
    endif

    ifeq ($(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5),Y)
        #@echo $(error AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5=$(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5))
        include $(THIRD_PARTY_DIR)/AT32F435_437_Firmware_Library_EN_V2.1.5/AT32F435_437_Firmware_Library_EN_V2_1_5_preconfig.mk
    endif

    ifeq ($(CMSIS),Y)
        #@echo $(error CMSIS=$(CMSIS))
        include $(THIRD_PARTY_DIR)/CMSIS/cmsis_preconfig.mk
    endif

    ifeq ($(EHAL_AT32F413),Y)
        #@echo $(error EHAL_AT32F413=$(EHAL_AT32F413))
        include $(THIRD_PARTY_DIR)/EHAL_AT32F413x/EHAL_AT32F413_preconfig.mk
    endif
    
    ifeq ($(EHAL_AT32F43X),Y)
        #@echo $(error EHAL_AT32F43X=$(EHAL_AT32F43X))
        include $(THIRD_PARTY_DIR)/EHAL_AT32F43X/EHAL_AT32F43X_preconfig.mk
    endif

    ifeq ($(EHAL_YTM32B1MX),Y)
        #@echo $(error EHAL_YTM32B1MX=$(EHAL_YTM32B1MX))
        include $(THIRD_PARTY_DIR)/EHAL_YTM32B1Mx/EHAL_YTM32B1M_preconfig.mk
    endif
    
    ifeq ($(FAT_FS),Y)
        #@echo $(error FAT_FS=$(FAT_FS))
        include $(THIRD_PARTY_DIR)/fat_fs/fat_fs_preconfig.mk
    endif

    ifeq ($(FREE_RTOS),Y)
        #@echo $(error FREE_RTOS=$(FREE_RTOS))
        include $(THIRD_PARTY_DIR)/FreeRTOS/free_rtos_preconfig.mk
    endif

    ifeq ($(MISCELLANEOUS),Y)
        #@echo $(error MISCELLANEOUS=$(MISCELLANEOUS))
        include $(THIRD_PARTY_DIR)/miscellaneous/miscellaneous_preconfig.mk
    endif

    ifeq ($(SENSITIVITY),Y)
        #@echo $(error SENSITIVITY=$(SENSITIVITY))
        include $(THIRD_PARTY_DIR)/sensitivity/sensitivity_preconfig.mk
    endif

endif