
ifeq ($(ARRAY),Y)
    TEST_ARRAY=Y
endif

ifeq ($(ALLOCATOR),Y)
    TEST_ALLOCATOR=Y
endif

ifeq ($(GPS),Y)
    TEST_GPS=Y
endif

ifeq ($(RUNNING_LINE),Y)
    RUNNING_LINE_WAV=Y
endif


ifeq ($(WAV),Y)
    TEST_WAV=Y
endif

ifeq ($(IIR),Y)
    TEST_IIR=Y
endif


ifeq ($(SET_GAME),Y)
    TEST_SET_GAME=Y
endif

ifeq ($(DELTA_SIGMA),Y)
    TEST_DELTA_SIGMA=Y
endif

ifeq ($(MATH_VECTOR),Y)
    TEST_MATH_VECTOR=Y
endif

ifeq ($(GPS_1BIT),Y)
    TEST_GPS_1BIT=Y
endif


ifeq ($(PLL_CALC),Y)
    TEST_PLL_CALC=Y
endif


ifeq ($(ISO_TP),Y)
    TEST_ISO_TP=Y
endif

ifeq ($(GNSS),Y)
    TEST_GNSS=Y
endif

ifeq ($(SOCKET),Y)
    TEST_SOCKET=Y
endif


ifeq ($(STRING_PARSER),Y)
    TEST_STRING_PARSER=Y
endif

ifeq ($(SCHMITT_TRIGGER),Y)
    TEST_SCHMITT_TRIGGER=Y
endif

ifeq ($(IEC16022),Y)
    TEST_IEC16022=Y
endif

ifeq ($(CALCULATOR),Y)
    TEST_CALCULATOR=Y
endif

ifeq ($(CONTROL),Y)
    TEST_CONTROL=Y
endif

ifeq ($(DISPLAY),Y)
    TEST_DISPLAY=Y
endif

ifeq ($(STACK_FRAME),Y)
    TEST_STACK_FRAME=Y
endif

ifeq ($(STATISTICS),Y)
    TEST_STATISTICS=Y
endif

ifeq ($(VOLTAGE_DIVIDER),Y)
    TEST_VOLTAGE_DIVIDER=Y
endif

ifeq ($(CRC),Y)
    TEST_CRC=Y
endif

ifeq ($(FIR),Y)
    TEST_FIR=Y
endif

ifeq ($(BASE16),Y)
    TEST_BASE16=Y
endif

ifeq ($(BASE64),Y)
    TEST_BASE64=Y
endif

ifeq ($(SUPER_CYCLE),Y)
    TEST_SUPER_CYCLE=Y
endif

ifeq ($(CSV),Y)
    TEST_CSV=Y
endif

ifeq ($(FONT),Y)
    TEST_FONT=Y
endif

ifeq ($(RLE),Y)
    TEST_RLE=Y
endif

ifeq ($(FFT),Y)
    TEST_FFT=Y
endif

ifeq ($(DFT),Y)
    TEST_DFT=Y
endif

ifeq ($(NOR_FLASH),Y)
    TEST_NOR_FLASH=Y
endif

ifeq ($(SW_NOR_FLASH),Y)
    TEST_SW_NOR_FLASH=Y
endif

ifeq ($(CIRCULAR_BUFFER),Y)
    TEST_CIRCULAR_BUFFER=Y
endif

ifeq ($(DS_TWR),Y)
    TEST_DS_TWR=Y
endif

ifeq ($(PHYSICS),Y)
    TEST_PHYSICS=Y
endif

ifeq ($(FIFO),Y)
    TEST_FIFO=Y
endif

ifeq ($(MODULATOR),Y)
    TEST_MODULATOR=Y
endif

ifeq ($(TBFP),Y)
    TEST_TBFP=Y
endif

ifeq ($(HASHSET),Y)
    TEST_HASHSET=Y
endif

ifeq ($(DECAWAVE),Y)
    TEST_DECAWAVE=Y
endif


ifeq ($(KEEPASS),Y)
    TEST_KEEPASS=Y
endif

ifeq ($(KEYBOARD),Y)
    TEST_KEYBOARD=Y
endif

ifeq ($(LIFO),Y)
    TEST_LIFO=Y
endif

ifeq ($(MATH),Y)
    TEST_MATH=Y
endif

ifeq ($(UTILS),Y)
    TEST_UTILS=Y
endif

ifeq ($(PLANETARIUM),Y)
    TEST_PLANETARIUM=Y
endif

ifeq ($(PROTOCOL),Y)
    TEST_PROTOCOL=Y
endif

ifeq ($(SALSA20),Y)
    TEST_SALSA20=Y
endif

ifeq ($(SHA256),Y)
    TEST_SHA256=Y
endif

ifeq ($(SOLVER),Y)
    TEST_SOLVER=Y
endif

ifeq ($(SET),Y)
    TEST_SET=Y
endif

ifeq ($(STRING),Y)
    TEST_STRING=Y
endif

ifeq ($(SW_NVRAM),Y)
    TEST_SW_NVRAM=Y
endif

ifeq ($(TIME),Y)
    TEST_TIME=Y
endif

TEST_SW=Y
UNIT_TEST=Y
