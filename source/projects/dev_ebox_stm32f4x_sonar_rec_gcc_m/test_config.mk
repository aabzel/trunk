ifneq ($(TEST_CONFIG_INC),Y)
    TEST_CONFIG_INC=Y

    TEST_MEMORY=Y

    ifeq ($(ADC),Y)
        TEST_ADC=Y
    endif

    ifeq ($(CORRELATOR_S16),Y)
        TEST_CORRELATOR_S16=N
    endif
    
    ifeq ($(BUTTON),Y)
        TEST_BUTTON=Y
    endif

    ifeq ($(SUPER_CYCLE),Y)
        TEST_SUPER_CYCLE=N
    endif

    ifeq ($(SONAR),Y)
        TEST_SONAR=N
    endif



    ifeq ($(NVIC),Y)
        TEST_NVIC=N
    endif

    ifeq ($(SOUND_RECORDER),Y)
        TEST_SOUND_RECORDER=Y
    endif

    ifeq ($(I2C),Y)
        TEST_I2C=Y
    endif
    
    ifeq ($(LOOPBACK_AUDIO),Y)
        TEST_LOOPBACK_AUDIO=Y
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

    ifeq ($(DDS),Y)
        TEST_DDS=Y
    endif

    ifeq ($(I2S),Y)
        TEST_I2S=Y
    endif

    ifeq ($(EXT_INT),Y)
        TEST_EXT_INT=Y
    endif

    ifeq ($(CSV),Y)
        TEST_CSV=Y
    endif

    ifeq ($(WAV_PLAYER),Y)
        TEST_WAV_PLAYER=Y
    endif


    ifeq ($(FAT_FS),Y)
        TEST_FAT_FS=N
    endif

    ifeq ($(I2S_FULL_DUPLEX),Y)
        #TEST_I2S_FULL_DUPLEX=Y
    endif

    ifeq ($(TIME),Y)
        TEST_TIME=N
    endif

    ifeq ($(SYSTICK),Y)
        TEST_SYSTICK=Y
    endif

    ifeq ($(SDIO),Y)
        TEST_SDIO=Y
    endif

    ifeq ($(WM8731),Y)
        TEST_WM8731=Y
    endif

    ifeq ($(TIMER),Y)
        TEST_TIMER=N
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