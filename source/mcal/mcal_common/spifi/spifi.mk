$(info SPIFI_COMMON_MCAL_MK_INC=$(SPIFI_COMMON_MCAL_MK_INC) )

ifneq ($(SPIFI_COMMON_MCAL_MK_INC),Y)
    SPIFI_COMMON_MCAL_MK_INC=Y

    SPIFI_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/spifi
    #@echo $(error SPIFI_COMMON_MCAL_DIR=$(SPIFI_COMMON_MCAL_DIR))

    INCDIR += -I$(SPIFI_COMMON_MCAL_DIR)
    OPT += -DHAS_SPIFI

    SOURCES_C += $(SPIFI_COMMON_MCAL_DIR)/spifi_general.c


    ifeq ($(SPIFI_ISR),Y)
        OPT += -DHAS_SPIFI_ISR
        SOURCES_C += $(SPIFI_COMMON_MCAL_DIR)/spifi_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SPIFI_DIAG),Y)
            OPT += -DHAS_SPIFI_DIAG
            SOURCES_C += $(SPIFI_COMMON_MCAL_DIR)/spifi_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SPIFI_COMMANDS),Y)
            OPT += -DHAS_SPIFI_COMMANDS
            SOURCES_C += $(SPIFI_COMMON_MCAL_DIR)/spifi_commands.c
        endif
    endif    
endif