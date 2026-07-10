ifneq ($(PCAN_PRO_X_PRECONFIG_INC),Y)
    PCAN_PRO_X_PRECONFIG_INC=Y

    MICROCONTROLLER=Y
    PCAN_PRO_X=Y
    STM32F407ZG=Y
    STM32=Y
    STM=Y
    #GPIO=Y
    #LED=Y
    #CAN=Y
    #CAN1=Y
    #CAN2=Y
    #PINS=Y
    #UART5=Y
    #UART=Y
    #USB=Y
    #LED=Y
    #LED_MONO=Y
    #USB_DEVICE=Y
    #USB_HS=Y
    #PWM=Y
endif
