$(info THIRD_PARTY_ASICS_PRECONFIG_INC=$(THIRD_PARTY_ASICS_PRECONFIG_INC) )
ifneq ($(THIRD_PARTY_ASICS_PRECONFIG_INC),Y)
    THIRD_PARTY_ASICS_PRECONFIG_INC=Y

    THIRD_PARTY_ASICS_DIR = $(THIRD_PARTY_DIR)/asics
    #@echo $(error THIRD_PARTY_ASICS_DIR=$(THIRD_PARTY_ASICS_DIR))

    ifeq ($(LIS3DH_EHAL),Y)
        #@echo $(error LIS3DH=$(LIS3DH))
        include $(THIRD_PARTY_ASICS_DIR)/lis3dh/lis3dh_preconfig.mk
    endif

    ifeq ($(NAU8814),Y)
        #@echo $(error NAU8814=$(NAU8814))
        include $(THIRD_PARTY_ASICS_DIR)/nau8814/nau8814_preconfig.mk
    endif

endif