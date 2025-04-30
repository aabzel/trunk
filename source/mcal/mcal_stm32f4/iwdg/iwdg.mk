$(info IWDG_MK_INC=$(IWDG_MK_INC) )
ifneq ($(IWDG_MK_INC),Y)
    IWDG_MK_INC=Y
    

    IWDG_DIR = $(MCAL_STM32F4_DIR)/iwdg
    #@echo $(error IWDG_DIR=$(IWDG_DIR))
    IWDG=Y
    INCDIR += -I$(IWDG_DIR)
    OPT += -DHAS_IWDG_CUSTOM

    SOURCES_C += $(IWDG_DIR)/iwdg_drv.c

    ifeq ($(CLI),Y)
        ifeq ($(IWDG_COMMANDS),Y)
            OPT += -DHAS_IWDG_COMMANDS
            SOURCES_C += $(IWDG_DIR)/iwdg_commands.c
        endif
    endif
endif


