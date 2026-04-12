#protection against repeated include as in C preprocessor
$(info DUMMY_MCU_PRECONFIG_INC=$(DUMMY_MCU_PRECONFIG_INC) )
ifneq ($(DUMMY_MCU_PRECONFIG_INC),Y)
    DUMMY_MCU_PRECONFIG_INC=Y
    #@echo $(error DUMMY_MCU_PRECONFIG_INC=$(DUMMY_MCU_PRECONFIG_INC))
    #CORTEX_M7=Y
    #FPU_HARD=Y
    MICROCONTROLLER=Y
    DUMMY_MCU=Y
endif
