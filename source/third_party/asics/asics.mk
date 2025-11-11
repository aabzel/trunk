$(info THIRD_PARTY_ASICS_MK_INC=$(THIRD_PARTY_ASICS_MK_INC) )
ifneq ($(THIRD_PARTY_ASICS_MK_INC),Y)
    THIRD_PARTY_ASICS_MK_INC=Y

    THIRD_PARTY_ASICS_DIR = $(THIRD_PARTY_DIR)/asics
    #@echo $(error THIRD_PARTY_ASICS_DIR=$(THIRD_PARTY_ASICS_DIR))

    INCDIR += -I$(THIRD_PARTY_ASICS_DIR)

    OPT += -DHAS_THIRD_PARTY_ASICS
    OPT += -DHAS_ASICS_CLI
    OPT += -DASICS_CLI_IN_USE

    ifeq ($(ASICS_COMMANDS),Y)
        OPT += -DHAS_ASICS_COMMANDS
    endif

    ifeq ($(LIS3DH_EHAL),Y)
        #@echo $(error LIS3DH=$(LIS3DH))
        include $(THIRD_PARTY_ASICS_DIR)/lis3dh/lis3dh.mk
    endif

    ifeq ($(NAU8814),Y)
        #@echo $(error NAU8814=$(NAU8814))
        include $(THIRD_PARTY_ASICS_DIR)/nau8814/nau8814.mk
    endif

    SOURCES_THIRD_PARTY_C +=  $(THIRD_PARTY_ASICS_DIR)/asics_initialize.c
    SOURCES_THIRD_PARTY_C +=  $(THIRD_PARTY_ASICS_DIR)/asics_routines.c
endif