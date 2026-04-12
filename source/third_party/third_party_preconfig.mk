
ifneq ($(THIRD_PARTY_PRECONFIG_INC),Y)
    THIRD_PARTY_PRECONFIG_INC=Y

    THIRD_PARTY_DIR = $(WORKSPACE_LOC)/third_party
    # $(error THIRD_PARTY_DIR= $(THIRD_PARTY_DIR))

    INCDIR += -I$(THIRD_PARTY_DIR)

    ifeq ($(ASICS),Y)
        # $(error ASICS=$(ASICS))
        include $(THIRD_PARTY_DIR)/asics/asics_preconfig.mk
    endif

    include $(THIRD_PARTY_DIR)/sdk/sdk_preconfig.mk

    ifeq ($(SERVICES),Y)
        # $(error SERVICES=$(SERVICES))
        include $(THIRD_PARTY_DIR)/Services/Services_preconfig.mk
    endif

    ifeq ($(FREE_RTOS),Y)
        # $(error FREE_RTOS=$(FREE_RTOS))
        include $(THIRD_PARTY_DIR)/FreeRTOS/free_rtos_preconfig.mk
    endif

    ifeq ($(MISCELLANEOUS),Y)
        # $(error MISCELLANEOUS=$(MISCELLANEOUS))
        include $(THIRD_PARTY_DIR)/miscellaneous/miscellaneous_preconfig.mk
    endif

    ifeq ($(SENSITIVITY),Y)
        # $(error SENSITIVITY=$(SENSITIVITY))
        include $(THIRD_PARTY_DIR)/sensitivity/sensitivity_preconfig.mk
    endif

endif