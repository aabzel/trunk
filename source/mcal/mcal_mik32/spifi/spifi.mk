$(info SPIFI_CUSTOM_MK_INC=$(SPIFI_CUSTOM_MK_INC) )
ifneq ($(SPIFI_CUSTOM_MK_INC),Y)
    SPIFI_CUSTOM_MK_INC=Y

    SPIFI_CUSTOM_DIR = $(MCAL_MIK32_DIR)/spifi
    #@echo $(error SPIFI_CUSTOM_DIR=$(SPIFI_CUSTOM_DIR))

    INCDIR += -I$(SPIFI_CUSTOM_DIR)

    SOURCES_C += $(SPIFI_CUSTOM_DIR)/spifi_mcal.c

    ifeq ($(SPIFI_ISR),Y)
        $(info + SPI ISR )
        OPT += -DHAS_SPIFI_ISR
        SOURCES_C += $(SPIFI_CUSTOM_DIR)/spifi_isr.c
    endif

    OPT += -DHAS_SPIFI_CUSTOM

    ifeq ($(SPIFI_WRITE),Y)
        OPT += -DHAS_SPIFI_WRITE
    endif
    
    ifeq ($(SPIFI_EXT),Y)
        OPT += -DHAS_SPIFI_EXT
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SPIFI_DIAG),Y)
            OPT += -DHAS_SPIFI_CUSTOM_DIAG
            SOURCES_C += $(SPIFI_CUSTOM_DIR)/spifi_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SPIFI_COMMANDS),Y)
            OPT += -DHAS_SPIFI_CUSTOM_COMMANDS
            SOURCES_C += $(SPIFI_CUSTOM_DIR)/spifi_custom_commands.c
        endif
    endif
endif