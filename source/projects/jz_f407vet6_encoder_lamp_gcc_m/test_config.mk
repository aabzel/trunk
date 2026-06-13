ifneq ($(TEST_CONFIG_INC),Y)
    TEST_CONFIG_INC=Y

    TEST_MEMORY=Y

    ifeq ($(ADC),Y)
        TEST_ADC=Y
    endif

    ifeq ($(NVIC),Y)
        TEST_NVIC=Y
    endif

    ifeq ($(IIR),Y)
        TEST_IIR=Y
    endif

ifeq ($(DRV8870),Y)
    TEST_DRV8870=Y
endif

    ifeq ($(TIME),Y)
        TEST_TIME=N
    endif

    ifeq ($(BICYCLE_HEADLAMP),Y)
        TEST_BICYCLE_HEADLAMP=Y
    endif

    ifeq ($(DAC),Y)
        TEST_DAC=Y
    endif

ifeq ($(RATIONAL_NUM),Y)
    TEST_RATIONAL_NUM=Y
endif

ifeq ($(INCREMENTAL_ENCODER),Y)
    TEST_INCREMENTAL_ENCODER=Y
endif



    ifeq ($(PLL_CALC),Y)
        TEST_PLL_CALC=Y
    endif

    ifeq ($(NVS),Y)
        TEST_NVS=Y
    endif

    ifeq ($(PWM),Y)
        TEST_PWM=Y
    endif


    ifeq ($(ENCODER_LAMP),Y)
        TEST_ENCODER_LAMP=Y
    endif

    ifeq ($(IQUEUE),Y)
        TEST_IQUEUE=Y
    endif
    
    ifeq ($(CAN),Y)
        TEST_CAN=Y
    endif
    
    ifeq ($(CAN_DIFF),Y)
        TEST_CAN_DIFF=Y
    endif

    ifeq ($(CAN_TX_PLANNER),Y)
        TEST_CAN_TX_PLANNER=Y
    endif

    ifeq ($(APPLICATIONS),Y)
        TEST_APPLICATIONS=Y
    endif

    ifeq ($(DELTA_SIGMA),Y)
        TEST_DELTA_SIGMA=Y
    endif

    ifeq ($(LED_MONO_PWM),Y)
        TEST_LED_MONO_PWM=Y
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

    ifeq ($(DWT),Y)
        TEST_DWT=Y
    endif

    ifeq ($(CSV),Y)
        TEST_CSV=Y
    endif

    ifeq ($(PARAM),Y)
        TEST_PARAM=Y
    endif

    ifeq ($(SI4703),Y)
        TEST_SI4703=Y
    endif

    ifeq ($(DAC_CHANNEL),Y)
        TEST_DAC_CHANNEL=Y
    endif

    ifeq ($(SYSTICK),Y)
        TEST_SYSTICK=Y
    endif

    ifeq ($(ENCODER_LAMP),Y)
        TEST_ENCODER_LAMP=Y
    endif

    ifeq ($(DELTA_SIGMA),Y)
        TEST_DELTA_SIGMA=Y
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        TEST_SOFTWARE_TIMER=Y
    endif

    ifeq ($(TIMER),Y)
        TEST_TIMER=Y
    endif

    ifeq ($(DSP),Y)
        TEST_DSP=Y
    endif

    ifeq ($(DMA_CHANNEL),Y)
        TEST_DMA_CHANNEL=Y
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

    ifeq ($(WATCHDOG),Y)
        TEST_WATCHDOG=Y
    endif
endif