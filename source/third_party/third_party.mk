ifneq ($(THIRD_PARTY_MK_INC),Y)
    THIRD_PARTY_MK_INC=Y

    THIRD_PARTY_DIR = $(WORKSPACE_LOC)/third_party
    # $(error THIRD_PARTY_DIR= $(THIRD_PARTY_DIR))
    MCAL_OPT += -DHAS_THIRD_PARTY

    INCDIR += -I$(THIRD_PARTY_DIR)

    ifeq ($(VENDOR_SDK),Y)
        include $(THIRD_PARTY_DIR)/sdk/sdk.mk
    endif

    ifeq ($(COMPUTING),Y)
        # $(error COMPUTING=$(COMPUTING))
        include $(THIRD_PARTY_DIR)/computing/computing.mk
    endif

    ifeq ($(THIRD_PARTY_LIBC),Y)
        include $(THIRD_PARTY_DIR)/libc/libc.mk
    endif

    ifeq ($(SERVICES),Y)
        # $(error SERVICES=$(SERVICES))
        include $(THIRD_PARTY_DIR)/Services/Services.mk
    endif

    ifeq ($(FREE_RTOS),Y)
        # $(error FREE_RTOS=$(FREE_RTOS))
        include $(THIRD_PARTY_DIR)/FreeRTOS/free_rtos.mk
    endif

    ifeq ($(THIRD_PARTY_ADT),Y)
        # $(error THIRD_PARTY_ADT=$(THIRD_PARTY_ADT))
        include $(THIRD_PARTY_DIR)/adt/adt.mk
    endif

    ifeq ($(THIRD_PARTY_ASICS),Y)
        # $(error THIRD_PARTY_ASICS=$(THIRD_PARTY_ASICS))
        include $(THIRD_PARTY_DIR)/asics/asics.mk
    endif

    ifeq ($(THIRD_PARTY_CONNECTIVITY),Y)
        # $(error THIRD_PARTY_CONNECTIVITY=$(THIRD_PARTY_CONNECTIVITY))
        include $(THIRD_PARTY_DIR)/connectivity/connectivity.mk
    endif

    ifeq ($(THIRD_PARTY_COMPUTING),Y)
        # $(error THIRD_PARTY_COMPUTING=$(THIRD_PARTY_COMPUTING))
        include $(THIRD_PARTY_DIR)/computing/computing.mk
    endif

    ifeq ($(THIRD_PARTY_SENSITIVITY),Y)
        # $(error THIRD_PARTY_SENSITIVITY=$(THIRD_PARTY_SENSITIVITY))
        include $(THIRD_PARTY_DIR)/sensitivity/sensitivity.mk
    endif

    ifeq ($(THIRD_PARTY_STORAGE),Y)
        # $(error THIRD_PARTY_STORAGE=$(THIRD_PARTY_STORAGE))
        include $(THIRD_PARTY_DIR)/storage/storage.mk
    endif

    ifeq ($(THIRD_PARTY_COMMANDS),Y)
        MCAL_OPT += -DHAS_THIRD_PARTY_COMMANDS
    endif

    ifeq ($(THIRD_PARTY_DIAG),Y)
        MCAL_OPT += -DHAS_THIRD_PARTY_DIAG
        SOURCES_THIRD_PARTY_C +=  $(THIRD_PARTY_DIR)/third_party_diag.c
    endif

endif