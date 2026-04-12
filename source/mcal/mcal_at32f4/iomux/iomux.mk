$(info IOMUX_CUSTOM_MK_INC=$(IOMUX_CUSTOM_MK_INC))
ifneq ($(IOMUX_CUSTOM_MK_INC),Y)
    IOMUX_CUSTOM_MK_INC=Y


    IOMUX_DIR = $(MCAL_AT32F4_DIR)/iomux
    #@echo $(error IOMUX_DIR=$(IOMUX_DIR))
    MCAL_OPT += -DHAS_IOMUX
    MCAL_OPT += -DHAS_IOMUX_CUSTOM

    INCDIR += -I$(IOMUX_DIR)

    SOURCES_C += $(IOMUX_DIR)/iomux_mcal.c

    ifeq ($(CLI),Y)
        ifeq ($(IOMUX_COMMANDS),Y)
            MCAL_OPT += -DHAS_IOMUX_CUSTOM_COMMANDS
            SOURCES_C += $(IOMUX_DIR)/iomux_custom_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(IOMUX_DIAG),Y)
            MCAL_OPT += -DHAS_IOMUX_CUSTOM_DIAG
            #@echo $(error IOMUX_DIAG=$(IOMUX_DIAG))
            SOURCES_C += $(IOMUX_DIR)/iomux_custom_diag.c
        endif
    endif
    
endif