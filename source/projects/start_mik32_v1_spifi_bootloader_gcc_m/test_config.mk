ifneq ($(TEST_CONFIG_INC),Y)
    TEST_CONFIG_INC=Y
    TEST_MEMORY=Y
    
    ifeq ($(STRING_READER),Y)
        TEST_STRING_READER=Y
    endif
    
    ifeq ($(ADC),Y)
        TEST_ADC=Y
    endif

    ifeq ($(DEBUGGER),Y)
        TEST_DEBUGGER=Y
    endif

    ifeq ($(CLI),Y)
        TEST_CLI=Y
    endif

    ifeq ($(EEPROM),Y)
        TEST_EEPROM=Y
    endif

    ifeq ($(ASICS),Y)
        TEST_ASICS=Y
    endif
    
    ifeq ($(W25Q32JV),Y)
        TEST_W25Q32JV=Y
    endif
    
    ifeq ($(FLASH_FS),Y)
        TEST_FLASH_FS=Y
    endif

    ifeq ($(SCR1_TIMER),Y)
        TEST_SCR1_TIMER=Y
    endif

    ifeq ($(TIME),Y)
        TEST_TIME=N
    endif

    ifeq ($(SPIFI),Y)
        TEST_SPIFI=Y
    endif

    ifeq ($(I2C),Y)
        TEST_I2C=Y
    endif
    
    ifeq ($(GPIO),Y)
        TEST_GPIO=N
    endif

    ifeq ($(NVS),Y)
        TEST_NVS=Y
    endif

    ifeq ($(FLOAT),Y)
        TEST_FLOAT=Y
    endif
    
    
    ifeq ($(PARAM),Y)
        TEST_PARAM=Y
    endif
    
    ifeq ($(UART),Y)
        TEST_UART=Y
    endif

    ifeq ($(MATH),Y)
        TEST_MATH=Y
    endif

    TEST_MISC=Y
    
    ifeq ($(UNIT_TEST),Y)
        TEST_SW=Y
        TEST_HW=Y
        OPT = -DHAS_TEST
        TEST=Y
    endif
endif