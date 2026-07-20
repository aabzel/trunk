ifneq ($(TEST_CONFIG_INC),Y)
    TEST_CONFIG_INC=Y


    TEST_MEMORY=Y
    TEST_IR_RECEIVER=Y

    ifeq ($(ADC),Y)
        TEST_ADC=Y
    endif

    ifeq ($(SUPER_CYCLE),Y)
        TEST_SUPER_CYCLE=Y
    endif

    ifeq ($(NVIC),Y)
        TEST_NVIC=Y
    endif

    ifeq ($(DMA_CHANNEL),Y)
        TEST_DMA_CHANNEL=Y
    endif

    ifeq ($(DDS),Y)
        TEST_DDS=Y
    endif

    ifeq ($(I2S),Y)
        TEST_I2S=Y
    endif

    ifeq ($(IR_SAMSUNG),Y)
        TEST_IR_SAMSUNG=Y
    endif

    ifeq ($(EXT_INT),Y)
        TEST_EXT_INT=Y
    endif

    ifeq ($(SHA256),Y)
        TEST_SHA256=Y
    endif

    ifeq ($(BASE64),Y)
        TEST_BASE64=Y
    endif

    ifeq ($(AES256),Y)
        TEST_AES256=Y
    endif

    ifeq ($(CSV),Y)
        TEST_CSV=Y
    endif
    ifeq ($(FDA801),Y)
        TEST_FDA801=Y
    endif

    ifeq ($(PARAM),Y)
        TEST_PARAM=Y
    endif

    ifeq ($(SI4737),Y)
        TEST_SI4737=Y
    endif

    ifeq ($(SI4703),Y)
        TEST_SI4703=Y
    endif

    ifeq ($(SYSTICK),Y)
        TEST_SYSTICK=Y
    endif

    ifeq ($(SDIO),Y)
        TEST_SDIO=Y
    endif

    ifeq ($(FAT_FS),Y)
        TEST_FAT_FS=Y
    endif

    ifeq ($(I2S_FULL_DUPLEX),Y)
        #TEST_I2S_FULL_DUPLEX=Y
    endif
    
    ifeq ($(TIME),Y)
        TES_TIMER=Y
    endif
    
    ifeq ($(SOFTWARE_TIMER),Y)
        TEST_SOFTWARE_TIMER=Y
    endif

    ifeq ($(WM8731),Y)
        TEST_WM8731=Y
    endif

    ifeq ($(TIMER),Y)
        TEST_TIMER=Y
    endif
    
    ifeq ($(COMPUTING),Y)
        TEST_COMPUTING=Y
    endif


    ifeq ($(SD_CARD),Y)
        TEST_SD_CARD=Y
    endif

    ifeq ($(UNIT_TEST),Y)
        TEST_SW=Y
        TEST_HW=Y
        MCAL_OPT = -DHAS_TEST
        TEST=Y
    endif
endif