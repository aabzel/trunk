ifneq ($(TBFP_PRECONFIG_MK),Y)
    TBFP_PRECONFIG_MK=Y

    $(info  Build  TBFP )
    TBFP=Y
    #CRC=Y
    #CRC8=Y
    FIFO=Y
    FIFO_CHAR=Y
    FIFO_INDEX=Y
    COMPUTING=Y
endif
