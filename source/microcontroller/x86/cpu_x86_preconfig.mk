#protection against repeated include as in C preprocessor
$(info X86_PRECONFIG_INC=$(X86_PRECONFIG_INC) )
ifneq ($(X86_PRECONFIG_INC),Y)
    X86_PRECONFIG_INC=Y
    #@echo $(error X86_PRECONFIG_INC=$(X86_PRECONFIG_INC))
    #AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5=Y
 
    MICROCONTROLLER=Y
 
 
endif
