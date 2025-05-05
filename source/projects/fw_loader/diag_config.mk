
DIAG=Y
BIT_DIAG=Y

ifeq ($(CALCULATOR),Y)
    CALCULATOR_DIAG=Y
endif

ifeq ($(CLOCK_DIVIDER),Y)
    CLOCK_DIVIDER_DIAG=Y
endif

ifeq ($(FLOAT),Y)
    FLOAT_DIAG=Y
endif

ifeq ($(SERIAL_PORT),Y)
    SERIAL_PORT_DIAG=Y
endif

ifeq ($(INTERFACES),Y)
    INTERFACES_DIAG=Y
endif

ifeq ($(INTERFACE),Y)
    INTERFACE_DIAG=Y
endif

ifeq ($(RUNNING_LINE),Y)
    RUNNING_LINE_DIAG=Y
endif

 
ifeq ($(PROTOCOL),Y)
    PROTOCOL_DIAG=Y
endif



ifeq ($(CLI),Y)
    CLI_DIAG=Y
endif

ifeq ($(DSP),Y)
    DSP_DIAG=Y
endif

ifeq ($(FFT),Y)
    FFT_DIAG=Y
endif

ifeq ($(WAV),Y)
    WAV_DIAG=Y
endif

ifeq ($(CIRCULAR_BUFFER),Y)
    CIRCULAR_BUFFER_DIAG=Y
endif

ifeq ($(IIR),Y)
    IIR_DIAG=Y
endif


ifeq ($(C_GENERATOR),Y)
    C_GENERATOR_DIAG=Y
endif

ifeq ($(SET_GAME),Y)
    SET_GAME_DIAG=Y
endif


ifeq ($(DELTA_SIGMA),Y)
    DELTA_SIGMA_DIAG=Y
endif

ifeq ($(KALAH),Y)
    KALAH_DIAG=Y
endif


ifeq ($(STRING_PARSER),Y)
    STRING_PARSER_DIAG=Y
endif

ifeq ($(DISPLAY),Y)
    DISPLAY_DIAG=Y
endif

ifeq ($(MATH_VECTOR),Y)
    MATH_VECTOR_DIAG=Y
endif

ifeq ($(PLL_SIM),Y)
    PLL_SIM_DIAG=Y
endif

ifeq ($(DFT),Y)
    DFT_DIAG=Y
endif

ifeq ($(TIMER_CALC),Y)
    TIMER_CALC_DIAG=Y
endif

ifeq ($(STORAGE),Y)
    STORAGE_DIAG=Y
endif

ifeq ($(GPS_1BIT),Y)
    GPS_1BIT_DIAG=Y
endif

ifeq ($(PLL_CALC),Y)
    PLL_CALC_DIAG=Y
endif

ifeq ($(SOCKET),Y)
    SOCKET_DIAG=Y
endif

ifeq ($(CRYP),Y)
    CRYP_DIAG=Y
endif

ifeq ($(TASK),Y)
    TASK_DIAG=Y
endif

ifeq ($(ISO_TP),Y)
    ISO_TP_DIAG=Y
endif

ifeq ($(CRC),Y)
    CRC_DIAG=Y
endif

ifeq ($(SUPER_CYCLE),Y)
    SUPER_CYCLE_DIAG=Y
endif

ifeq ($(LIFO_ARRAY),Y)
    LIFO_ARRAY_DIAG=Y
endif

ifeq ($(DTMF),Y)
    DTMF_DIAG=Y
endif

ifeq ($(CONTROL),Y)
    CONTROL_DIAG=Y
endif


ifeq ($(GNSS),Y)
    GNSS_DIAG=Y
endif

ifeq ($(COMPLEX),Y)
    COMPLEX_DIAG=Y
endif

ifeq ($(GPS),Y)
    GPS_DIAG=Y
endif

ifeq ($(COMPLEX),Y)
    COMPLEX_DIAG=Y
endif

ifeq ($(STACK_FRAME),Y)
    STACK_FRAME_DIAG=Y
endif

ifeq ($(VOLTAGE_DIVIDER),Y)
    VOLTAGE_DIVIDER_DIAG=Y
endif

ifeq ($(ARRAY),Y)
    ARRAY_DIAG=Y
endif

ifeq ($(RS485),Y)
    RS485_DIAG=Y
endif

ifeq ($(LOG),Y)
    LOG_DIAG=Y
endif

ifeq ($(FOURIER_SERIES),Y)
    FOURIER_SERIES_DIAG=Y
endif

ifeq ($(FIR),Y)
    FIR_DIAG=Y
endif

ifeq ($(RLE),Y)
    RLE_DIAG=Y
endif

ifeq ($(APPLICATIONS),Y)
    APPLICATIONS_DIAG=Y
endif

ifeq ($(CALENDAR),Y)
    CALENDAR_DIAG=Y
endif

ifeq ($(FONT),Y)
    FONT_DIAG=Y
endif

ifeq ($(DS_TWR),Y)
    DS_TWR_DIAG=Y
endif

ifeq ($(PLANETARIUM),Y)
    PLANETARIUM_DIAG=Y
endif

ifeq ($(NOR_FLASH),Y)
    NOR_FLASH_DIAG=Y
endif

ifeq ($(LIFO),Y)
    LIFO_DIAG=Y
endif

ifeq ($(NOR_FLASH),Y)
    NOR_FLASH_DIAG=Y
endif

ifeq ($(DECAWAVE),Y)
    DECAWAVE_DIAG=Y
endif

ifeq ($(TIME),Y)
    TIME_DIAG=Y
endif

ifeq ($(SW_NVRAM),Y)
    SW_NVRAM_DIAG=Y
endif

ifeq ($(MODULATOR),Y)
    MODULATOR_DIAG=Y
endif

ifeq ($(PHYSICS),Y)
    PHYSICS_DIAG=Y
endif

ifeq ($(KEYBOARD),Y)
    KEYBOARD_DIAG=Y
endif

ifeq ($(DDS),Y)
    DDS_DIAG=Y
endif

ifeq ($(SYSTEM),Y)
    SYSTEM_DIAG=Y
endif

ifeq ($(BASE64),Y)
    BASE64_DIAG=Y
endif

ifeq ($(IEC16022),Y)
    IEC16022_DIAG=Y
endif

ifeq ($(FIFO),Y)
    FIFO_DIAG=Y
endif

ifeq ($(HASHSET),Y)
    HASHSET_DIAG=Y
endif

ifeq ($(SALSA20),Y)
    SALSA20_DIAG=Y
endif

ifeq ($(SHA256),Y)
    SHA256_DIAG=Y
endif

ifeq ($(STATISTICS),Y)
    STATISTICS_DIAG=Y
endif

ifeq ($(TBFP),Y)
    TBFP_DIAG=Y
endif

ifeq ($(SOLVER),Y)
    SOLVER_DIAG=Y
endif

ifeq ($(MATH),Y)
    MATH_DIAG=Y
endif

SW_DIAG=Y
UTILS_DIAG=Y

ifeq ($(UNIT_TEST),Y)
    UNIT_TEST_DIAG=Y
endif
