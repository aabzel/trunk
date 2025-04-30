
ifneq ($(AT32_MK_INC),Y)
    AT32_MK_INC=Y

    CMSIS=Y
    MCAL_AT32=Y
    CORTEX_M=Y
    MICROCONTROLLER=Y
    #include $(WORKSPACE_LOC)/core/cortex_m4/cortex_m4.mk
endif
