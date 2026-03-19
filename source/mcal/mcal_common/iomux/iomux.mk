$(info IOMUX_GENERAL_DRV_MK_INC=$(IOMUX_GENERAL_DRV_MK_INC) )
ifneq ($(IOMUX_GENERAL_DRV_MK_INC),Y)
    IOMUX_GENERAL_DRV_MK_INC=Y

    IOMUX_MCAL_DIR = $(MCAL_COMMON_DIR)/iomux
    #@echo $(error IOMUX_MCAL_DIR=$(IOMUX_MCAL_DIR))

    INCDIR += -I$(IOMUX_MCAL_DIR)
    MCAL_OPT += -DHAS_IOMUX

    SOURCES_C += $(IOMUX_MCAL_DIR)/iomux_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(IOMUX_DIAG),Y)
            MCAL_OPT += -DHAS_IOMUX_DIAG
            SOURCES_C += $(IOMUX_MCAL_DIR)/iomux_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(IOMUX_COMMANDS),Y)
            MCAL_OPT += -DHAS_IOMUX_COMMANDS
            SOURCES_C += $(IOMUX_MCAL_DIR)/iomux_commands.c
        endif
    endif
    
endif