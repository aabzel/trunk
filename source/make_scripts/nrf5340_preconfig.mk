#protection a  gainst repeated include as in C preprocessor
ifneq ($(NRF5340_PRECONFIG_MK_INC),Y)
    NRF5340_PRECONFIG_MK_INC=Y

    MICROCONTROLLER=Y
    NRFX=Y
    MCAL=Y
    CORTEX_M33=Y
    NRF5340=Y
    MCAL_NRF5340=Y
    NRF5340_APP=Y
    
endif