$(info CORTEX_SELECT_MK_INC=$(CORTEX_SELECT_MK_INC) )
ifneq ($(CORTEX_SELECT_MK_INC),Y)
    CORTEX_SELECT_MK_INC=Y


    CORE_CUSTOM_DIR = $(CORE_DIR)/cortex_m7
    INCDIR += -I$(CORE_CUSTOM_DIR)
    # $(error CORE_CUSTOM_DIR=$(CORE_CUSTOM_DIR))

    SOURCES_C += $(CORE_CUSTOM_DIR)/cortex_m7_driver.c

    MCAL_OPT += -DHAS_ARM
    MCAL_OPT += -DHAS_CORTEX_M7
    MCAL_OPT += -DHAS_CORTEX_M

    ifeq ($(NVIC),Y)
        #include $(CORTEX_M7_DIR)/nvic/nvic.mk
    endif

    MICROPROCESSOR += -mcpu=cortex-m7 
    MICROPROCESSOR += -march=armv7e-m
    MICROPROCESSOR += -mthumb  
    
    ifeq ($(FPU),Y)
        #MCAL_OPT += -D__FPU_PRESENT=1
        #MCAL_OPT += -D__FPU_USED=1
        MICROPROCESSOR += -mfpu=fpv5-sp-d16
        MICROPROCESSOR += -mfloat-abi=hard
    else
        MICROPROCESSOR += -mfloat-abi=soft
    endif

    ifeq ($(SYSTICK),Y)
        # $(error SYSTICK=$(SYSTICK))
        #include $(CORE_CUSTOM_DIR)/systick/systick.mk
    endif
    
    
    
        
    ifeq ($(DIAG),Y)
        ifeq ($(CORTEX_M7_DIAG),Y)
            MCAL_OPT += -DHAS_CORTEX_M7_DIAG
            SOURCES_C += $(CORE_CUSTOM_DIR)/cortex_m7_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(CORTEX_M7_COMMANDS),Y)
            #$(error CORTEX_M7_COMMANDS=$(CORTEX_M7_COMMANDS))
            MCAL_OPT += -DHAS_CORTEX_M7_COMMANDS
            SOURCES_C += $(CORE_CUSTOM_DIR)/cortex_m7_commands.c
        endif
    endif
    
endif