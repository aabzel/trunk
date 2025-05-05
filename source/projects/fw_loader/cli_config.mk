$(info CLI_CONFIG_MK_INC=$(CLI_CONFIG_MK_INC) )
ifneq ($(CLI_CONFIG_MK_INC),Y)
    CLI_CONFIG_MK_INC=Y

    #$(error Build  $(mkfile_path) )
    CLI=Y
    CLI_CMD_HISTORY=N
    CLI_NATIVE_COMMANDS=Y

    BIT_COMMANDS=Y
    ifeq ($(WAV),Y)
        WAV_COMMANDS=Y
    endif

    ifeq ($(SERIAL_PORT),Y)
        SERIAL_PORT_COMMANDS=Y
    endif
    
    ifeq ($(RUNNING_LINE),Y)
        RUNNING_LINE_COMMANDS=Y
    endif

    ifeq ($(C_GENERATOR),Y)
        C_GENERATOR_COMMANDS=Y
    endif

    ifeq ($(CIRCULAR_BUFFER),Y)
        CIRCULAR_BUFFER_COMMANDS=Y
    endif

    ifeq ($(SET_GAME),Y)
        SET_GAME_COMMANDS=Y
    endif

    ifeq ($(DELTA_SIGMA),Y)
        DELTA_SIGMA_COMMANDS=Y
    endif

    ifeq ($(KALAH),Y)
        KALAH_COMMANDS=Y
    endif

    ifeq ($(GAMES),Y)
        GAMES_COMMANDS=Y
    endif

    ifeq ($(STRING_READER),Y)
        STRING_READER_COMMANDS=Y
    endif

    ifeq ($(PLL_SIM),Y)
        PLL_SIM_COMMANDS=Y
    endif

    ifeq ($(MATH),Y)
        MATH_COMMANDS=Y
    endif


    ifeq ($(MATH_VECTOR),Y)
        MATH_VECTOR_COMMANDS=Y
    endif


    ifeq ($(SOCKET),Y)
        SOCKET_COMMANDS=Y
    endif

    ifeq ($(TIMER_CALC),Y)
        TIMER_CALC_COMMANDS=Y
    endif

    ifeq ($(GPS_1BIT),Y)
        GPS_1BIT_COMMANDS=Y
    endif

    ifeq ($(GNSS),Y)
        GNSS_COMMANDS=Y
    endif

    ifeq ($(PLL_CALC),Y)
        PLL_CALC_COMMANDS=Y
    endif

    ifeq ($(GPS),Y)
        GPS_COMMANDS=Y
    endif

    ifeq ($(ANALOG_FILTER),Y)
        ANALOG_FILTER_COMMANDS=Y
    endif

    ifeq ($(BOOT),Y)
        BOOT_COMMANDS=Y
    endif

    ifeq ($(ISO_TP),Y)
        ISO_TP_COMMANDS=Y
    endif

    ifeq ($(DTMF),Y)
        DTMF_COMMANDS=Y
    endif
    
    ifeq ($(LIFO_ARRAY),Y)
        LIFO_ARRAY_COMMANDS=Y
    endif

    ifeq ($(CALCULATOR),Y)
        CALCULATOR_COMMANDS=Y
    endif

    ifeq ($(CONVERTOR),Y)
        CONVERTOR_COMMANDS=Y
    endif

    ifeq ($(STACK_FRAME),Y)
        STACK_FRAME_COMMANDS=Y
    endif

    ifeq ($(COMPLEX),Y)
        COMPLEX_COMMANDS=Y
    endif

    ifeq ($(DISPLAY),Y)
        DISPLAY_COMMANDS=Y
    endif

    ifeq ($(INTERFACES),Y)
        INTERFACES_COMMANDS=Y
    endif

    ifeq ($(SW_DAC),Y)
        SW_DAC_COMMANDS=Y
    endif

    ifeq ($(RS485),Y)
        RS485_COMMANDS=Y
    endif

    ifeq ($(ARRAY),Y)
        ARRAY_COMMANDS=Y
    endif

    ifeq ($(IIR),Y)
        IIR_COMMANDS=Y
    endif

    ifeq ($(PROTOCOLS),Y)
        PROTOCOLS_COMMANDS=Y
    endif
    
    ifeq ($(CALENDAR),Y)
        CALENDAR_COMMANDS=Y
    endif

    ifeq ($(RLE),Y)
        RLE_COMMANDS=Y
    endif

    ifeq ($(VOLTAGE_DIVIDER),Y)
        VOLTAGE_DIVIDER_COMMANDS=Y
    endif

    ifeq ($(SENSITIVITY),Y)
        SENSITIVITY_COMMANDS=Y
    endif

    ifeq ($(APPLICATIONS),Y)
        APPLICATIONS_COMMANDS=Y
    endif

    ifeq ($(DECAWAVE),Y)
        DECAWAVE_COMMANDS=Y
    endif

    ifeq ($(FONT),Y)
        FONT_COMMANDS=Y
    endif

    ifeq ($(COMPUTING),Y)
        COMPUTING_COMMANDS=Y
    endif

    ifeq ($(ALLOCATOR),Y)
        ALLOCATOR_COMMANDS=Y
    endif

    ifeq ($(FOURIER_SERIES),Y)
        FOURIER_SERIES_COMMANDS=Y
    endif

    ifeq ($(CLOCK),Y)
        CLOCK_COMMANDS=Y
    endif
    
    ifeq ($(TIME),Y)
        TIME_COMMANDS=Y
    endif
    
    ifeq ($(KEEPASS),Y)
        KEEPASS_COMMANDS=Y
    endif

    ifeq ($(PLANETARIUM),Y)
        PLANETARIUM_COMMANDS=Y
    endif

    ifeq ($(DS_TWR),Y)
        DS_TWR_COMMANDS=Y
    endif

    ifeq ($(NOR_FLASH),Y)
        NOR_FLASH_COMMANDS=Y
    endif

    ifeq ($(CONNECTIVITY),Y)
        CONNECTIVITY_COMMANDS=Y
    endif

    ifeq ($(FAT_FS),Y)
        FAT_FS_COMMANDS=Y
    endif

    ifeq ($(SW_NOR_FLASH),Y)
        SW_NOR_FLASH_COMMANDS=Y
    endif

    ifeq ($(DSP),Y)
        DSP_COMMANDS=Y
    endif
    
    ifeq ($(FIR),Y)
        FIR_COMMANDS=Y
    endif

    ifeq ($(CSV),Y)
        CSV_COMMANDS=Y
    endif

    ifeq ($(IEC16022),Y)
        IEC16022_COMMANDS=Y
    endif

    ifeq ($(SW_NVRAM),Y)
        SW_NVRAM_COMMANDS=Y
    endif

    ifeq ($(STORAGE),Y)
        STORAGE_COMMANDS=Y
    endif

    ifeq ($(TBFP),Y)
        TBFP_COMMANDS=Y
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        SOFTWARE_TIMER_COMMANDS=Y
    endif

    ifeq ($(SOLUTIONS),Y)
        SOLUTIONS_COMMANDS=Y
    endif

    ifeq ($(SOLVER),Y)
        SOLVER_COMMANDS=Y
    endif

    ifeq ($(SOLVER_SLAE),Y)
        SOLVER_SLAE_COMMANDS=Y
    endif

    ifeq ($(SUPER_CYCLE),Y)
        SUPER_CYCLE_COMMANDS=Y
    endif

    ifeq ($(PASTILDA),Y)
        PASTILDA_COMMANDS=Y
    endif

    ifeq ($(CONTROL),Y)
        CONTROL_COMMANDS=Y
    endif

    ifeq ($(STATISTICS),Y)
        STATISTICS_COMMANDS=Y
    endif

    ifeq ($(PROBABILITY_TRIANGLE),Y)
        PROBABILITY_TRIANGLE_COMMANDS=Y
    endif

    ifeq ($(TASK),Y)
        TASK_COMMANDS=Y
    endif
    
    ifeq ($(LOG),Y)
        LOG_COMMANDS=Y
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        HEALTH_MONITOR_COMMANDS=Y
    endif



    UNIT_TEST_COMMANDS=Y
    DEBUGGER_COMMANDS=Y
endif