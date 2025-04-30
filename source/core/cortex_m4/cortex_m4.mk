$(info CORTEX_SELECT_MK_INC=$(CORTEX_SELECT_MK_INC) )
ifneq ($(CORTEX_SELECT_MK_INC),Y)
    CORTEX_SELECT_MK_INC=Y

    CORTEX_SEL_DIR = $(CORE_DIR)/cortex_m4
    INCDIR += -I$(CORTEX_SEL_DIR)
    #@echo $(error CORTEX_SEL_DIR=$(CORTEX_SEL_DIR))

    MICROCONTROLLER=Y
    SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_driver.c
    OPT += -DHAS_ARM
    OPT += -DHAS_CORTEX_M4
    OPT += -DHAS_CORTEX_M

    ifeq ($(NVIC),Y)
        include $(CORTEX_SEL_DIR)/nvic/nvic.mk
    endif
    
    ifeq ($(DIAG),Y)
        ifeq ($(CORTEX_M4_DIAG),Y)
            OPT += -DHAS_CORTEX_M4_DIAG
            SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(CORTEX_M4_COMMANDS),Y)
            OPT += -DHAS_CORTEX_M4_COMMANDS
            SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_commands.c
        endif
    endif

    MICROPROCESSOR += -mcpu=cortex-m4 
    MICROPROCESSOR += -march=armv7e-m
    MICROPROCESSOR += -mthumb

    ifeq ($(FPU),Y)
        OPT += -DHAS_FPU
        MICROPROCESSOR += -mfloat-abi=hard
        MICROPROCESSOR += -mfpu=fpv4-sp-d16
    else
        MICROPROCESSOR += -mfloat-abi=soft
    endif

    ifeq ($(SYSTICK),Y)
        #@echo $(error SYSTICK=$(SYSTICK))
        include $(CORTEX_SEL_DIR)/systick/systick.mk
    endif
endif