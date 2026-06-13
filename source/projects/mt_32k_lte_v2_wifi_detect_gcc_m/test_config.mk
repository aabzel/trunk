ifneq ($(TEST_CONFIG_INC),Y)
    TEST_CONFIG_INC=N

    TEST_MEMORY=N

    ifeq ($(ADC),Y)
        TEST_ADC=N
    endif

    ifeq ($(STORE_FS),Y)
        TEST_STORE_FS=N
    endif

    ifeq ($(WIFI),Y)
        TEST_WIFI=N
    endif

    ifeq ($(NVIC),Y)
        TEST_NVIC=N
    endif

    ifeq ($(LITTLE_FS),Y)
        TEST_LITTLE_FS=N
    endif

ifeq ($(RTC),Y)
    TEST_RTC=N
endif


ifeq ($(NMEA),Y)
    TEST_NMEA=N
endif

    ifeq ($(MATH),Y)
        TEST_MATH=N
    endif

    ifeq ($(IIR),Y)
        TEST_IIR=N
    endif

    ifeq ($(MX25L6433F),Y)
        TEST_MX25L6433F=Y
    endif

    ifeq ($(MATH_VECTOR),Y)
        TEST_MATH_VECTOR=N
    endif
    
    ifeq ($(GNSS_PROVE),Y)
        TEST_GNSS_PROVE=N
    endif

    ifeq ($(SLIDING_INTEGRAL),Y)
        TEST_SLIDING_INTEGRAL=N
    endif

    ifeq ($(DAC),Y)
        TEST_DAC=N
    endif

ifeq ($(RATIONAL_NUM),Y)
    TEST_RATIONAL_NUM=N
endif

ifeq ($(SCHEDULER),Y)
    TEST_SCHEDULER=N
endif

ifeq ($(GNSS),Y)
    TEST_GNSS=N
endif

    ifeq ($(LOCAL_OSCILLATOR),Y)
        TEST_LOCAL_OSCILLATOR=N
    endif

    ifeq ($(PLL_CALC),Y)
        TEST_PLL_CALC=N
    endif

    ifeq ($(NVS),Y)
        TEST_NVS=N
    endif

ifeq ($(INTERRUPT),Y)
    TEST_INTERRUPT=N
endif


    ifeq ($(PWM),Y)
        TEST_PWM=N
    endif

    ifeq ($(SPI_DEVICE),Y)
        TEST_SPI_DEVICE=N
    endif

ifeq ($(ESP_01),Y)
    TEST_ESP_01=Y
endif

    ifeq ($(SPI),Y)
        TEST_SPI=Y
    endif

    ifeq ($(IQUEUE),Y)
        TEST_IQUEUE=N
    endif

    ifeq ($(CAN),Y)
        TEST_CAN=N
    endif
    
    ifeq ($(CAN_DIFF),Y)
        TEST_CAN_DIFF=N
    endif

    ifeq ($(CAN_TX_PLANNER),Y)
        TEST_CAN_TX_PLANNER=N
    endif

    ifeq ($(APPLICATIONS),Y)
        TEST_APPLICATIONS=N
    endif

    ifeq ($(ISO_TP),Y)
        TEST_ISO_TP=N
    endif

    ifeq ($(LED_MONO_PWM),Y)
        TEST_LED_MONO_PWM=N
    endif

ifeq ($(GPIO),Y)
    TEST_GPIO=N
endif

    ifeq ($(EXT_INT),Y)
        TEST_EXT_INT=N
    endif

    ifeq ($(SHA256),Y)
        TEST_SHA256=N
    endif

    ifeq ($(BASE64),Y)
        TEST_BASE64=N
    endif

    ifeq ($(DWT),Y)
        TEST_DWT=N
    endif

    ifeq ($(CSV),Y)
        TEST_CSV=N
    endif

    ifeq ($(DAC_CHANNEL),Y)
        TEST_DAC_CHANNEL=N
    endif

    ifeq ($(SYSTICK),Y)
        TEST_SYSTICK=N
    endif


    ifeq ($(SOFTWARE_TIMER),Y)
        TEST_SOFTWARE_TIMER=N
    endif

    ifeq ($(TIMER),Y)
        TEST_TIMER=N
    endif

    ifeq ($(DSP),Y)
        TEST_DSP=N
    endif

    ifeq ($(DMA_CHANNEL),Y)
        TEST_DMA_CHANNEL=N
    endif

    ifeq ($(UNIT_TEST),Y)
        TEST_SW=Y
        TEST_HW=Y
        MCAL_OPT = -DHAS_TEST
        TEST=Y
    endif

    ifeq ($(WATCHDOG),Y)
        TEST_WATCHDOG=N
    endif
endif