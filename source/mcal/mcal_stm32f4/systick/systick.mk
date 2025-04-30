
ifneq ($(SYSTICK_CUSTOM_MK_INC),Y)
    SYSTICK_CUSTOM_MK_INC=Y

    
    CUSTOM_SYSTICK_DIR = $(MCAL_STM32F4_DIR)/systick
    #@echo $(error SYSTICK_DIR=$(SYSTICK_DIR))
    INCDIR += -I$(CUSTOM_SYSTICK_DIR)
    OPT += -DHAS_SYSTICK_CUSTOM
    OPT += -DHAS_SYSTICK_INT

    SOURCES_C += $(CUSTOM_SYSTICK_DIR)/systick_custom.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(CUSTOM_SYSTICK_DIR)/systick_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CUSTOM_SYSTICK_COMMANDS),Y)
            OPT += -DHAS_CUSTOM_SYSTICK_COMMANDS
            SOURCES_C += $(CUSTOM_SYSTICK_DIR)/systick_custom_commands.c
        endif
    endif
endif