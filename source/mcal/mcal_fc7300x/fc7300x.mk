
ifneq ($(FC7300X_MK_INC),Y)
    FC7300X_MK_INC=Y

    CMSIS=Y
    MCAL_FC7300X=Y
    CORTEX_M=Y
    CORTEX_M7=Y
    ARM=Y
    MICROCONTROLLER=Y
    #include $(WORKSPACE_LOC)/core/cortex_m4/cortex_m4.mk
endif
