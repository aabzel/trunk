$(info GENERIC_MK_INC=$(GENERIC_MK_INC) )
ifneq ($(GENERIC_MK_INC),Y)
    GENERIC_MK_INC=Y

    #ifeq ($(KEY_VAL_MAP),Y)
    #    include $(WORKSPACE_LOC)/make_scripts/key_val_map.mk
    #endif

    #ARRAY needed for Flash
    #ADT=Y
    #ARRAY=Y
    #ARRAY_EXT=Y
    #MATH_LIB=Y
    ##CLOCK_DIAG=Y
    #SUPER_CYCLE_DIAG=Y
    #TASK_DIAG=Y
    #BOARD=Y
    #NUM_DIAG=Y
    #BOOT=Y
    #BOOT_DIAG=Y
    #CLOCK=Y
    #CONTROL=Y
    #CONTROL_COMMANDS=Y
    #CONNECTIVITY=Y
    #COMMON=Y
    #COMPONENTS=Y
    #COMPUTING=Y
    #CORE=Y
    ##CORE_EXT=Y
    ##CRC=Y
    ##CRC32=Y
    #DATA_POC=Y
    #DIAG=Y
    #LOG_UTILS=Y
    ##FLASH_FS=Y
    ##FLASH_FS_WRITE=Y
    ##FLASH_NVS=Y
    ##FLASH_NVS_WRITE=Y
    ##FLASH_WRITE=Y
    #FLOAT_UTILS=Y
    ##HAL_RCC_EX=Y
    #HEALTH_MONITOR=Y
    ##IWDG=Y
    #MATH=Y
    #MICROCONTROLLER=Y
    ##PARAM_DIAG=Y
    ##PARAM_SET=Y
    #STRING=Y
    #SUPER_LOOP=Y
    #SYS_INIT=Y
    #SYSTEM=Y
    #TASK=Y
    #TIME=Y
    ##TIMER=Y not for Nrf5340
    ##UART=Y
    #UTILS_EXT=Y
    #UTILS=Y
    #OPT += -DHAS_TYPE_CALC
    #OPT += -DHAS_DEBUG
    #OPT += -DHAS_GENERIC
    #ifeq ($(MICROCONTROLLER),Y)
    #    OPT += -DHAS_MCU
    #    OPT += -DHAS_MICROCONTROLLER
    #    MCAL=Y
    #    INTERRUPT=Y
    #    GPIO=Y
    #endif
    #
    #ifeq ($(NORTOS),Y)
    #    OPT += -DHAS_NORTOS
    #endif
    #
    #OPT += -DHAS_STR2_DOUBLE
    #OPT += -DHAS_STR2_FLOAT
    #OPT += -DHAS_UTILS_STRING
    #
    ##include $(WORKSPACE_LOC)/bsp/bsp.mk
    #ifeq ($(TERMINAL),Y)
    #    #$(error TERMINAL=$(TERMINAL) )
    #    include $(WORKSPACE_LOC)/make_scripts/terminal.mk
    #endif
endif
