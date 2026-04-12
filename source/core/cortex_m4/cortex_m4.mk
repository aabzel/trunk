$(info CORTEX_SELECT_MK_INC=$(CORTEX_SELECT_MK_INC) )
ifneq ($(CORTEX_SELECT_MK_INC),Y)
    CORTEX_SELECT_MK_INC=Y

    CORTEX_SEL_DIR = $(CORE_DIR)/cortex_m4
    INCDIR += -I$(CORTEX_SEL_DIR)
    # $(error CORTEX_SEL_DIR=$(CORTEX_SEL_DIR))

    MICROCONTROLLER=Y
    SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_driver.c
    MCAL_OPT += -DHAS_ARM
    MCAL_OPT += -DHAS_CORTEX_M4
    MCAL_OPT += -DHAS_CORTEX_M
    
    ifeq ($(DIAG),Y)
        ifeq ($(CORTEX_M4_DIAG),Y)
            MCAL_OPT += -DHAS_CORTEX_M4_DIAG
            SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CORTEX_M4_COMMANDS),Y)
            MCAL_OPT += -DHAS_CORTEX_M4_COMMANDS
            SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_commands.c
        endif
    endif

    MICROPROCESSOR += -mcpu=cortex-m4 
    MICROPROCESSOR += -march=armv7e-m
    MICROPROCESSOR += -mthumb
    
    ifeq ($(MPU),Y)
        MCAL_OPT += -D__MPU_PRESENT=1
    endif

    ifeq ($(FPU),Y)
        MCAL_OPT += -DHAS_FPU
        #MCAL_OPT += -D__FPU_PRESENT=1
        #MCAL_OPT += -D__FPU_USED=1
        MICROPROCESSOR += -mfloat-abi=hard
        MICROPROCESSOR += -mfpu=fpv4-sp-d16
    else
        MICROPROCESSOR += -mfloat-abi=soft
    endif

endif