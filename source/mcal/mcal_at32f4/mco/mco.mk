$(info MCO_DRV_MK_INC=  $(MCO_DRV_MK_INC) )
ifneq ($(MCO_DRV_MK_INC),Y)
    MCO_DRV_MK_INC=Y

    MCO_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/mco
    #@echo $(error MCO_CUSTOM_DIR=$(MCO_CUSTOM_DIR))

    INCDIR += -I$(MCO_CUSTOM_DIR)
    OPT += -DHAS_MCO

    ifeq ($(MCO1),Y)
        OPT += -DHAS_MCO1
    endif

    ifeq ($(MCO2),Y)
        OPT += -DHAS_MCO2
    endif

    OPT += -DHAS_MCO
    SOURCES_C += $(MCO_CUSTOM_DIR)/mco_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(MCO_DIAG),Y)
            OPT += -DHAS_MCO_DIAG
            SOURCES_C += $(MCO_CUSTOM_DIR)/mco_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MCO_COMMANDS),Y)
            #@echo $(error MCO_COMMANDS=$(MCO_COMMANDS))
            OPT += -DHAS_MCO_COMMANDS
            SOURCES_C += $(MCO_CUSTOM_DIR)/mco_commands.c
        endif
    endif
endif