$(info MCO_DRV_MK_INC=  $(MCO_DRV_MK_INC) )
ifneq ($(MCO_DRV_MK_INC),Y)
    MCO_DRV_MK_INC=Y

    MCO_STM_DIR = $(MCAL_STM32F4_DIR)/mco
    #@echo $(error MCO_STM_DIR=$(MCO_STM_DIR))

    INCDIR += -I$(MCO_STM_DIR)
    OPT += -DHAS_MCO_CUSTOM

    ifeq ($(MCO1),Y)
        OPT += -DHAS_MCO1
    endif

    ifeq ($(MCO2),Y)
        OPT += -DHAS_MCO2
    endif

    OPT += -DHAS_MCO
    SOURCES_C += $(MCO_STM_DIR)/mco_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(MCO_DIAG),Y)
            OPT += -DHAS_MCO_DIAG
            SOURCES_C += $(MCO_STM_DIR)/mco_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MCO_COMMANDS),Y)
            #@echo $(error MCO_COMMANDS=$(MCO_COMMANDS))
            OPT += -DHAS_MCO_COMMANDS
            SOURCES_C += $(MCO_STM_DIR)/mco_commands.c
        endif
    endif
endif