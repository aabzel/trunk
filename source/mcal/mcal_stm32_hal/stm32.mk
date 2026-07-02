
ifneq ($(STM32_MK_INC),Y)
    STM32_MK_INC=Y

    CMSIS=Y
    STM_HAL=Y
    MCAL_STM32=Y
    CORTEX_M=Y
    MICROCONTROLLER=Y
    #include $(WORKSPACE_LOC)/core/cortex_m4/cortex_m4.mk
endif
