ifneq ($(TEST_CONFIG_INC),Y)
    TEST_CONFIG_INC=Y

    TEST_MEMORY=Y


    ifeq ($(BUTTON),Y)
        TEST_BUTTON=Y
    endif

    ifeq ($(SUPER_CYCLE),Y)
        TEST_SUPER_CYCLE=N
    endif

    ifeq ($(FLASH_FS),Y)
        TEST_FLASH_FS=Y
    endif

    ifeq ($(NVIC),Y)
        TEST_NVIC=Y
    endif

    ifeq ($(STORE_FS),Y)
        TEST_STORE_FS=Y
    endif
    
    ifeq ($(ILI9341),Y)
        TEST_ILI9341=Y
    endif

    ifeq ($(FILE_MCAL),Y)
        TEST_FILE_MCAL=Y
    endif

    ifeq ($(DMA_CHANNEL),Y)
        TEST_DMA_CHANNEL=Y
    endif
    
    ifeq ($(COMPUTING),Y)
        TEST_COMPUTING=Y
    endif

    ifeq ($(LITTLE_FS),Y)
        TEST_LITTLE_FS=Y
    endif

    ifeq ($(BIN_ADC),Y)
        TEST_BIN_ADC=Y
    endif

    ifeq ($(EXT_INT),Y)
        TEST_EXT_INT=Y
    endif

    ifeq ($(CSV),Y)
        TEST_CSV=Y
    endif

    ifeq ($(GPIO),Y)
        TEST_GPIO=Y
    endif

    ifeq ($(FAT_FS),Y)
        TEST_FAT_FS=Y
    endif

    ifeq ($(TIME),Y)
        TEST_TIME=N
    endif

    ifeq ($(SYSTICK),Y)
        TEST_SYSTICK=Y
    endif

    ifeq ($(SPI),Y)
        TEST_SPI=Y
    endif

    ifeq ($(UTF8_STR),Y)
        TEST_UTF8_STR=Y
    endif

    ifeq ($(BIN_DAC),Y)
        TEST_BIN_DAC=Y
    endif

    ifeq ($(TIMER),Y)
        TEST_TIMER=Y
    endif

    ifeq ($(UART),Y)
        TEST_UART=Y
    endif

    ifeq ($(UNIT_TEST),Y)
        TEST_SW=Y
        TEST_HW=Y
        MCAL_OPT = -DHAS_TEST
        TEST=Y
    endif
endif